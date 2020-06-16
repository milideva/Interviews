
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

/* Not handling negative numbers and with 0x i.e. 0x19 etc */
int str_digit_to_num (char ch) {

    if (ch >= '0' && ch <= '9') {
        return ch - '0';
    }

    ch = toupper(ch);
    if (ch >= 'A' && ch <= 'F') {
        return 10+ ch - 'A';
    }

    return -1;
}

/* Not handling negative numbers  and with 0x i.e. 0x19 etc */
int hex_to_dec (char *hex_str) 
{
    if (!hex_str) return -1;
    int num = 0;
    
    while (*hex_str != '\0') {
        int digit = str_digit_to_num(*hex_str);
        
        if (digit == -1) return -1;
        num = 16 * num + digit;
        hex_str++;
    }
    return num;
}

/* Not handling negative numbers or 0x19 etc */
int binary_to_dec (char *bin_str) 
{
    if (!bin_str) return -1;
    int num = 0;
    
    while (*bin_str != '\0') {
        char ch = *bin_str;
        int digit;
        if (ch == '0') 
            digit = 0;
        else if (ch == '1') 
            digit = 1;
        else 
            return -1;
        num = 2 * num + digit;
        bin_str++;
    }
    return num;
}

bool compare_binary_hex_str (char *bin_str, char *hex_str) 
{
    int n1 = binary_to_dec(bin_str);
    int n2 = hex_to_dec(hex_str);
    printf("binary2dec(%s):%d hex2dec(%s):%d\n", bin_str, n1, hex_str, n2);
    if (n1<0 || n2<0) return false;
    return (n1 == n2);
}

int main (void) {
    char *bin_str = "1010";
    char *hex_str = "a";

    printf("bin_str:%s hex_str:%s is %s \n", bin_str, hex_str,
           compare_binary_hex_str(bin_str, hex_str) ? "true" : "false");
    hex_str = "0a";
    printf("bin_str:%s hex_str:%s is %s \n", bin_str, hex_str,
           compare_binary_hex_str(bin_str, hex_str) ? "true" : "false");
    bin_str = "001010";
    printf("bin_str:%s hex_str:%s is %s \n", bin_str, hex_str,
           compare_binary_hex_str(bin_str, hex_str) ? "true" : "false");

    hex_str = "a0";
    printf("bin_str:%s hex_str:%s is %s \n", bin_str, hex_str,
           compare_binary_hex_str(bin_str, hex_str) ? "true" : "false");
    return 0;
}
