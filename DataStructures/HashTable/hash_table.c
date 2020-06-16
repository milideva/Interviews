#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_HT_BUCKETS  100

typedef struct node {
    char *key;
    void *value;
    struct node *next; //collision , save next. To avoid this, have series of hash functions.

/*   Increase bucket size or # hash functions to increase capacity
   Using just three hash functions increases the load to 91%
*/
} node;

// A hash table is just an array of these nodes 
// node *table[MAX_HT_BUCKETS]
// collisions are just in a singly linked list LIFO


// A Hash Function: the returned hash value will be the 
// ASCII value of the first character of the string
// modulo the size of the table.
unsigned int hash (const char *str, int tablesize) {
    int value;
    value = toupper(str[0]) - 'A';
    return value % tablesize;
}


// This should return the data for given key
static void *lookup (node *table[], const char *key) {
    unsigned index = hash(key, MAX_HT_BUCKETS);
    const node *it = table[index];

    // Try to find if a matching key in the list exists
    while (it != NULL && strcmp(it->key, key) != 0) {
        it = it->next;
    }
    if (it) return it->value;
    return NULL;
}

bool insert (node *table[], char *key) {
    if (!lookup(table, key)) {
        // Find the desired linked list
        unsigned index = hash(key, MAX_HT_BUCKETS);

        node *new_node = malloc(sizeof *new_node);
        if (new_node == NULL)
            return false;

        new_node->key = malloc(strlen(key)+1);
        if (new_node->key == NULL) {
            free(new_node);
            return false;
        }

        // Add the new key and link to the front of the list
        strcpy(new_node->key, key);
        new_node->next = table[index];
        table[index] = new_node;

        return true;
    }
    return false;
}

// Populate Hash Table
// First parameter: The hash table variable
// Second parameter: The name of the text file with the words
int populate_hash (node *table[], FILE *file) {
    char word[50];
    char c;

    do {
        c = fscanf(file, "%s", word);
        // IMPORTANT: remove newline character
        size_t ln = strlen(word) - 1;
        if (word[ln] == '\n')
            word[ln] = '\0';

        printf("inserting %s\n", word);
        insert(table, word);
    } while (c != EOF);

    return 1;
}

node **create_hash_table (unsigned capacity) {
    node **table = calloc(capacity, sizeof *table);
    return table;
}

int main (int argc, char **argv) {
    char word[50];
    char c;
    int found = 0;

    // Initialize the hash table
    //node *table[MAX_HT_BUCKETS] = {0};
    node **table = create_hash_table(MAX_HT_BUCKETS);

    FILE *INPUT;
    INPUT = fopen("INPUT", "r");
    // Populate hash table
    populate_hash(table, INPUT);
    fclose(INPUT);
    printf("The hash table is ready!\n");

    int line = 0;
    FILE *CHECK;
    CHECK = fopen("CHECK", "r");

    do {
        c = fscanf(CHECK, "%s", word);

        // IMPORTANT: remove newline character
        size_t ln = strlen(word) - 1;
        if (word[ln] == '\n')
            word[ln] = '\0';

        line++;
        if (lookup(table, word)) {
            found++;
        }
    } while (c != EOF);

    printf("Found %d words in the hash table!\n", found);

    fclose(CHECK);
    return 0;
}
