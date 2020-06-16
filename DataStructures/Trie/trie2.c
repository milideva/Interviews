#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ALPHABETS (26)

typedef struct trie {
    int value;
    struct trie *children[ALPHABETS];
} trie_t;

struct trie *create_node (void) {
    return calloc(1, sizeof(trie_t));
}

int num_words;

int get_index (char *key, int i) {
    int index = -1;
    if (key[i] >= 'a' && key[i] <= 'z') {
        index = key[i] - 'a';
    } else if (key[i] >= 'A' && key[i] >= 'Z') {
        index = key[i] - 'A';
    }
    return index;
}

int search (trie_t *t, char *key) {
    if (!key || !t) return 0;
    
    int i, str_len = strlen(key);
    
    for (i = 0; i < str_len; i++) {
        int index = get_index(key, i);
        if (index == -1) return index;
        trie_t *child = t->children[index];
        if (!child) {
            return 0;
        }
        t = child;
    }
    printf("%s: %s val:%d\n", __FUNCTION__, key, t->value);
    return t->value;
}

int insert (trie_t *t, char key[]) {
    if (!t) return 0;

    int i, str_len = strlen(key);
    num_words++;

    for (i = 0; i < str_len; i++) {
        int index = get_index(key, i);
        if (index == -1) {
            return 0;
        }
        trie_t *child = t->children[index];
        
        if (!child) {
            child = create_node();
            if (!child) return 0;
            t->children[index] = child;
        }
        t = child;
    }
    //printf("%s: added %s val:%d\n", __FUNCTION__, key, num_words);
    t->value = num_words;
    return 1;
}

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

int main() {
    int i;
    // Input keys (use only 'a' through 'z' and lower case)
    char keys[][8] = {"the", "a", "there", "answer", "any", "by", "bye", "their"};
    trie_t *trie = create_node();
 
    char output[][32] = {"Not present in trie", "Present in trie"};
 

    for(i = 0; i < ARRAY_SIZE(keys); i++) {
        insert(trie, keys[i]);
    }
 
    // Search for different keys
    printf("%s --- %s\n", "the", output[search(trie, "the") ? 1 : 0] );
    printf("%s --- %s\n", "these", output[search(trie, "these") ? 1 : 0] );
    printf("%s --- %s\n", "their", output[search(trie, "their") ? 1 : 0] );
    printf("%s --- %s\n", "thaw", output[search(trie, "thaw") ? 1 : 0] );
 
    return 0;
}
