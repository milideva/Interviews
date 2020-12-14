
#include <stdio.h>

int make_change (int n, int denom) {
    int next_denom = 0;

    switch (denom) {
      case 25 :
        next_denom = 10;
        break;
      case 10 :
        next_denom = 5;
        break;  
       case 5 :
         next_denom = 1;
         break;  
      case 1:
        return 1;
    }

    int i, ways = 0;
    for (i = 0; i*denom <= n; i++) {
        ways += make_change(n - i*denom, next_denom);
    }

    return ways;

}


int main (void) {
    int n = 10;
    int ways = make_change(n, 25);
    printf("Change of %d cents can be done in %d ways\n", n, ways);
    
    n = 75;
    ways = make_change(n, 25);
    printf("Change of %d cents can be done in %d ways\n", n, ways);
    
    return 0;
}
