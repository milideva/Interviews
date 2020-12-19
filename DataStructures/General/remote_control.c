/*

Given the English alphabet, 'a' through 'z' (lowercase), and an imaginary onscreen keyboard with the letters laid out in 6 rows and 5 columns:

a b c d e
f g h i j
k l m n o
p q r s t
u v w x y
z

0 1 2 3 4
5 6 7 8 9
10 ..

Using a remote control - 
(up - 'u', down 'd', left 'l', right 'r' and enter '!'), write a function that
given a word will produce the sequence of key presses required to type out the
word on the onscreen keyboard. The function should return the sequence
string. 

*/

#define COLS (5)
     
void get_path (char src, char dst) {
    int s, d;
    /* TODO Handle capital letters also */
    s = src - 'a';
    d = dst - 'a';
    while (s != d) {
        if (s == 'z'-'a') {
            printf("up "); s -= COLS;
            continue;
        }
        if ((s % COLS) > (d % COLS)) {
            printf("l "); s--;
        } else if ((s % COLS) < (d % COLS)) {
            printf("r "); s++;
        } else {
            /* Columns match move up or down */
            if (s > d) {
                printf("up "); s -= COLS; 
            } else {
                printf("down "); s += COLS; 
            }
        }
    }
}

void remote (char *str) {

    printf("path for string ::%s::\n", str);
    while (*str) {
        if (*(str+1) == '\0') {
            break;
        }
        printf("\n%c --> %c : ", *str, *(str+1));
        get_path(*str, *(str+1));
        str++;
    }
    printf("\n");
}

int main () {
    char *str= "zebra";
    remote(str);
}
