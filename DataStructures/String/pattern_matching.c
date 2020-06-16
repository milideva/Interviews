
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* The following algo is O(m * n) 
   m is in_len and n is pat_len.
   For a better algorithm, google for
   Knuth Morris Pratt(KMP) Pattern Matching(Substring search) 
   KMP is O(m+n)

   char *strstr(const char *haystack, const char *needle);
          
 */

int pattern_match (char *input, char *pattern) {
    int in_len, pat_len, match_len, pos;
    
    if (!input || !pattern) return false;
    
    in_len = strlen(input);
    pat_len = strlen(pattern);

    if (in_len < pat_len) return false;

    match_len = pos = 0;
    char *orig_pattern = pattern;
    
    while (*input != '\0') {
        
        if (*input == *pattern) {
            pattern++;
            match_len++;
            if (match_len == pat_len) {
                return pos-pat_len+1;
            }
        } else {
            if (match_len) {
                pattern = orig_pattern;
                input -= (match_len-1);
                match_len = 0;
            }
        }

        input++;
        pos++;
    }

    return -1;
}

int main (void) {
    char *in = "devdatta";
    char *pattern = "da";
    int pos = pattern_match(in, pattern);

    printf("in:%s pattern:%s %s at %d \n", in, pattern, 
           pos == -1 ? "not matched" : "matched", pos);

    in = "abcbcglx";
    pattern = "bcgl";

    pos = pattern_match(in, pattern);

    printf("in:%s pattern:%s %s at %d \n", in, pattern, 
           pos == -1 ? "not matched" : "matched", pos);

    return 0;
}
