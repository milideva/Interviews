/*
  Find the longest substring with k unique characters in a given string

Given a string you need to print longest possible substring that has exactly M
unique characters. If there are more than one substring of longest possible
length, then print any one of them.

Examples:

"aabbcc", k = 1
Max substring can be any one from {"aa" , "bb" , "cc"}.

"aabbcc", k = 2
Max substring can be any one from {"aabb" , "bbcc"}.

"aabbcc", k = 3
There are substrings with exactly 3 unique characters
{"aabbcc" , "abbcc" , "aabbc" , "abbc" }
Max is "aabbcc" with length 6.

"aaabbb", k = 3
There are only two unique characters, thus show error message. 

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int uint;

/* This is O(n) solution.  
   
 Idea is to maintain a window and add elements to the window till it contains
 less or equal k, update our result if required while doing so.

 If unique elements exceeds than required in window, start removing the
 elements from left side.
*/

/* Assumptions : this is ascii and not uni-code */
uint count_longest_uniq_substr (char *str, uint k) {

    uint count, uniq, start, end, longest, longest_start, i;
    i = uniq = count = start =  end = longest = longest_start = 0;
    
    if (!str || !k) return count;
    
    uint len = strlen(str);

    uint ascii[256] = { 0 };

    /* add first char */
    ascii[str[i] - 'a'] = 1;
    uniq = 1;

    for (i=1; i < len; i++) {
        end = i;

        if (ascii[str[i] - 'a'] == 0) {
            uniq++; // Uniq char so far
        }
        ascii[str[i] - 'a']++;

        while (uniq > k) {
            ascii[str[start] - 'a']--;
            if (ascii[str[start] - 'a'] == 0) {
                uniq--; // Uniq char so far
            }
            start++; /* Advance the sliding window by 1 char from start */
            continue;
        }

        if (longest < (end - start)+1) {
            longest = end - start + 1;
            longest_start = start;
        }
        
    }

    printf("Inputs : str:%s, k:%d\n", str, k);
    printf("longest_start:%d, longest:%d\n", longest_start, longest);
    char *my = malloc(longest+1);
    strncpy(my, str+longest_start, longest);
    my[longest+1] = '\0';
    printf("my longest %d unique char.s substr: %s\n", k, my);
    return count;
}


int main (void) {

    char * str = "aabacbebebe";

    count_longest_uniq_substr(str, 3);

    return 0;
}
