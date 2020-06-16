#include <stdio.h>

#define make_string(x) #x
#define COMMA ,

int main () {
	char *str;
	str = make_string(twas brillig);
	printf("%s\n", str);
// 1. no surprise here
// "twas brillig"

	str = make_string( twas      brillig );
// 2. leading and trailing spaces were trimmed, 
// space between words was compressed to a single space character "twas brillig"
        printf("%s\n", str);

	str = make_string("twas" "brillig");
// 3. the quotes were automatically converted---> "\"twas\" \"brillig\""
        printf("%s\n", str);

	str = make_string(twas COMMA brillig);
// 4. the macro COMMA was not expanded ----> "twas COMMA brillig"
// space between words was compressed to a single space character "twas brillig"
        printf("%s\n", str);

        str = make_string("twas" "brillig");
// 5. the quotes were automatically converted---> "\"twas\" \"brillig\""
        printf("%s\n", str);

	return 0;
}
