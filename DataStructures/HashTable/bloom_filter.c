#include <stdlib.h>
#include <stdio.h>

#include <stddef.h>
#include <stdbool.h>

typedef unsigned int (*hash_function)(const void *data);
typedef struct bloom_filter * bloom_t;

struct bloom_hash_funcs {
    hash_function func;
    struct bloom_hash_funcs *next;
};

struct bloom_filter {
    struct bloom_hash_funcs *func;
    void *bits; // points to size #bytes
    size_t size; // in bytes
};

bloom_t bloom_create (size_t size) {
	bloom_t res = calloc(1, sizeof(struct bloom_filter));
	res->size = size;
	res->bits = calloc(1, size);
	return res;
}

void bloom_free (bloom_t filter) {
	if (filter) {
		while (filter->func) {
			struct bloom_hash_funcs *h;
			filter->func = h->next;
			free(h);
		}
		free(filter->bits);
		free(filter);
	}
}

void bloom_add_hash_funcs (bloom_t filter, hash_function func) {
	struct bloom_hash_funcs *h = calloc(1, sizeof(struct bloom_hash_funcs));
	h->func = func;
	struct bloom_hash_funcs *last = filter->func;
	while (last && last->next) {
		last = last->next;
	}
	if (last) {
		last->next = h;
	} else {
		filter->func = h;
	}
}

void bloom_add (bloom_t filter, const void *item) {
	struct bloom_hash_funcs *h = filter->func;
	uint8_t *bits = filter->bits;
	while (h) {
		unsigned int hash = h->func(item);
		hash %= filter->size * 8;
		bits[hash / 8] |= 1 << hash % 8;
		h = h->next;
	}
}

bool bloom_test (bloom_t filter, const void *item) {
	struct bloom_hash_funcs *h = filter->func;
	uint8_t *bits = filter->bits;
	while (h) {
		unsigned int hash = h->func(item);
		hash %= filter->size * 8;
		if (!(bits[hash / 8] & 1 << hash % 8)) {
			return false;
		}
		h = h->next;
	}
	return true;
}

unsigned int djb2 (const void *_str) {
	const char *str = _str;
	unsigned int hash = 5381;
	char c;
	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

unsigned int jenkins (const void *_str) {
	const char *key = _str;
	unsigned int hash, i;
	while (*key) {
		hash += *key;
		hash += (hash << 10);
		hash ^= (hash >> 6);
		key++;
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

int main () {
	bloom_t bloom = bloom_create(8);
	bloom_add_hash_funcs(bloom, djb2);
	bloom_add_hash_funcs(bloom, jenkins);
	printf("Should be 0: %d\n", bloom_test(bloom, "hello world"));
	bloom_add(bloom, "hello world");
	printf("Should be 1: %d\n", bloom_test(bloom, "hello world"));
	printf("Should (probably) be 0: %d\n", bloom_test(bloom, "world hello"));
	return 0;
}

