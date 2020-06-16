#include <string.h>
#include <stdio.h>

/*
  phoneKeyboard

Given a keypad as shown in diagram, and a n digit number, list all words which
are possible by pressing these numbers.  For example if input number is 234,
possible words which can be formed are (Alphabetical order): adg adh adi aeg
aeh aei afg afh afi bdg bdh bdi beg beh bei bfg bfh bfi cdg cdh cdi ceg ceh
cei cfg cfh cfi

How many words are possible with seven digits with each digit representing n
letters? For first digit we have at most four choices, and for each choice for
first letter, we have at most four choices for second digit and so on. So it's
simple maths it will be O(4^n). Since keys 0 and 1 don't have any
corresponding alphabet and many characters have 3 characters, 4^n would be the
upper bound of number of words and not the minimum words.

*/

const char digits_arr[10] [5]= { "",  /* 0 */
                                 "",  /* 1 */
                                 "abc", /* 2 */
                                 "def", /* 3 */
                                 "ghi", /* 4 */
                                 "jkl", /* 5 */
                                 "mno", /* 6 */
                                 "pqrs",/* 7 */
                                 "tuv", /* 8 */
                                 "wxyz",/* 9 */
};
                     
static void phone2string (int phone_array[], int phone_num_digits, 
                          int curr_digit_index, char output[]) {

    if (curr_digit_index == phone_num_digits) {
        printf("output = %s\n", output);
        return;
    }
    int digit = phone_array[curr_digit_index];
    int num_chars = strlen(digits_arr[digit]);
    int i;
    //printf("%d, %d, %d\n", phone_num_digits, curr_digit_index, num_chars);
    for (i = 0; i < num_chars; i++) {
        output[curr_digit_index] = digits_arr[digit][i];
        phone2string(phone_array, phone_num_digits, 
                     curr_digit_index+1, output);
    }
    
}

int main () {
#define INPUT_DIGITS  (5)
    int input_phone[INPUT_DIGITS] = { 5, 5, 5, 5, 5};
    char output[INPUT_DIGITS+1];

    memset(output, sizeof(output), 0);

    phone2string(input_phone, sizeof(input_phone)/sizeof(input_phone[0]),
                 0,  output);

    return 0;
}
    

