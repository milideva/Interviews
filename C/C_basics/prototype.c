#include <stdio.h>

/* ANSI way of telling no argument with void */
void foobar1(void)  {   
    printf("In foobar1\n");  
}

/* The following func is without prototype.
   May be a K&R type. Says *nothing* about arguments.
*/
void foobar2()  {   
    printf("In foobar2\n");  
    /* Does complie : with a warning */
}

int main()  {     
        foobar1();     
        foobar2(33, 'a');     
        return 0;  
}
