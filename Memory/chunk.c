#include <string.h>
#include <stdlib.h>

typedef struct chunk_type_ chunk_type;

struct chunk_type_ {
    int size; // size of each chunk
    int num_elem; // total number of chunks
    char *free_list[0];
    int free_index;
};


chunk_type *create_chunk (int size, int num_elem) {
    int data_sz = size * num_elem;

    if (!data_sz) return NULL;

    chunk_type *chunk;
    int malloc_sz, header_sz = sizeof(*chunk); 
    int free_list_sz = num_elem * sizeof(char *); //free list array
    
    malloc_sz = data_sz + free_list_sz + header_sz;
    
    chunk = malloc(malloc_sz);
    if (!chunk) return NULL;

    memset(chunk, 0, malloc_sz);
    chunk->size = size;
    chunk->num_elem = num_elem;
    int i;
    char *data = ((char *) chunk) -  data_sz;

    for (i=0; i<num_elem; i++) {
        chunk->free_list[i] = data;
        data = data + size;
    }

    chunk->free_index = num_elem-1;

    return chunk;
}

void *chunk_malloc (chunk_type *chunk) {
    if (!chunk->free_index) return NULL;

    int index = --chunk->free_index;
    void * data = chunk->free_list[index];
    
    return data;
}

void chunk_free (chunk_type *chunk, void *data) {
    int index = chunk->free_index + 1;
    chunk->free_list[index] = data;
    chunk->free_index++;
}

int main () {

}
