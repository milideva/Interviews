/* A child is running up stairs and can take 1 or 2 or 3 steps a time.
   how many ways can the child hop up N stairs?
*/

/* 
   Steps Count
   0     1 <------  This is the key.
   1     1  
   2     2 (1,1) (2)
   3     4 (1,1,1) (1,2) (2,1) (3)
   4     7 (1,1,1,1) (1,2,1) (1,1,2) (1,3) (2,1,1) (2,2) (3,1)
   5     13
*/

#include <stdio.h>
#include <string.h>

int count_ways (int n) {

    if (n < 0) return 0;
    if (n == 0) return 1;
    return count_ways(n-1) + count_ways(n-2) + count_ways(n-3);
}

/* This is exponential 3 ^ N */
/* Fix is to use dynamic programming */

long count_ways_dp (int n, long array[]) {
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (array[n] > -1) {
        return array[n];
    }
    array[n] = count_ways_dp(n-1, array) + 
        count_ways_dp(n-2, array) + 
        count_ways_dp(n-3, array);
    return array[n];
}

void test (n) {
    long ret;
    ret = count_ways(n);
    printf("count_ways(%d)=%d\n", n, ret);

    long array[100];
    memset(array, -1, sizeof(array));
    ret = count_ways_dp(n, array);
    printf("count_ways(%d)=%d\n", n, ret);
}

int main () {
    test(5);
    test(10);
    return 0;
}
