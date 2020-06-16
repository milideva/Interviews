#include <stdio.h>
#include <limits.h>


/* Checking for overflow is tricky */

int reverse (int x){
    int ret = 0;
    
    while (x) {
        int r = x % 10;
        if (ret > INT_MAX/10) return 0;
        if (ret < INT_MIN/10) return 0;

        ret = ret *10 + r;
        x = x/10;
    }
    return ret;
}

int main (void) {
    int ret = reverse(1534236469);
    printf("ret:%d for 1534236469\n", ret);

    ret = reverse(-123567);
    printf("ret:%d for -123567\n", ret);

    return 0;
}

