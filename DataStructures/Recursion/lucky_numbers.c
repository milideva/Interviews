
/* 

Lucky Numbers

Lucky numbers are subset of integers. Rather than going into much theory, let
us see the process of arriving at lucky numbers,

Take the set of integers
1,2,3,4,5,6,7,8,9,10,11,12,14,15,16,17,18,19,??

First, delete every second number, we get following reduced set.
1,3,5,7,9,11,13,15,17,19,????

Now, delete every third number, we get
1, 3, 7, 9, 13, 15, 19,?.?.

Continue this process indefinitely??
Any number that does NOT get deleted due to above process is called lucky.

Therefore, set of lucky numbers is 1, 3, 7, 13,

bool isLucky(int n)

*/

#include <stdio.h>
#include <stdbool.h>

bool isLucky (int n) {

    static int step = 2;
    
    if (step > n) return true;

    if (n%step == 0) return false;

    n = n - n/step; /* n/step numbers will be unlucky, remove those */

    step++;

    return isLucky(n);
}


int main (void) {

  int x = 19;
  
  if( isLucky(x) )
    printf("%d is a lucky no.", x);
  else
    printf("%d is not a lucky no.", x);

  getchar();  

}
