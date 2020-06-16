#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
 
typedef struct trie {
    int words;
    int prefixes;
    struct trie *edges[26];
} trie;
 
trie *addWord (trie *ver, char *str) {
    if (!str) return NULL;
    
    char k = tolower(str[0]);
    int index = k - 'a';

    printf("%c",str[0]);

    if (k == '\0') {
        ver->words += 1;
        return ver;
    }

    if (!ver->edges[index]) {
        ver->edges[index] = calloc(1, sizeof(trie));
    }

    ver->prefixes += 1;

    ver->edges[index] = addWord(ver->edges[index], ++str);
    
    return ver;
}
 
int countWords (trie *ver,char *str) {
    if (str[0]=='\0')
        return ver->words;
    
    int k = tolower(str[0])-'a';
    str++;
    if (ver->edges[k]==NULL)
        return 0;

    return countWords(ver->edges[k],str);
}
 
int countPrefix (trie *ver, char *str) {
    if (str[0]=='\0')
        return ver->prefixes;

    int k = tolower(str[0])-'a';
    str++;

    if(ver->edges[k]==NULL)
        return 0;

    return countPrefix(ver->edges[k], str);
}
 
int main() {
    trie *start = calloc(1, sizeof(trie));

    int ch = 1;
    while (ch) {
        printf("\n 1. Insert a word ");
        printf("\n 2. Count words");
        printf("\n 3. Count prefixes");
        printf("\n 0. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d",&ch);
        char input[1000];
        switch(ch) {
          case 1:
            printf("\nEnter a word to insert: ");
            scanf("%s",input);
            start = addWord(start, input);
            break;
          case 2:
            printf("\nEnter a word to count words: ");
            scanf("%s",input);
            printf("\n answer %d\n", countWords(start, input));
            break;
          case 3:
            printf("\nEnter a word to count prefixes: ");
            scanf("%s",input);
            printf("\n answer %d\n", countPrefix(start, input));
            break;
        }
    }

    return 0;
}
