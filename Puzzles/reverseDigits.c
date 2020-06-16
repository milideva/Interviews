
/* num = 4356; */

int reverseDigits (int num) {
    int reverse = 0;

    while (num) {
        reverse = reverse * 10 + num % 10;
        num /= 10;
    }

    return reverse;
}

int main() {
    int i = 123456;
    int j = reverseDigits(i);
    printf("num:%d reverse:%d\n", i, j);
    return 0;
}
    
