#include <stdio.h>
#include <string.h>

void swap (char *a, char *b) {
    char temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void permute (char *a, int start, int end) {
    int i;
    // base case
    if (start == end) {
        printf("%s\n", a);
        return;
    }
 
    // try all permutations
    for (i = start; i <= end; i++) {
        swap(a + start, a + i);
        permute(a, start + 1, end);
        swap(a + start, a + i); // backtrack
    }
}

int main (void) {
    char a[100];
    printf("Input a string for doing permutations: ");
    gets(a);
    
    permute(a, 0, strlen(a) - 1);
    return 0;
}
