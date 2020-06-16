#include <stdio.h>

void foobar1(void)  {   
    printf("In foobar1\n");  
}
void foobar2()  {  
    printf("In foobar2\n");  
}
int main()  {     
    char ch = 'a';     
    foobar1(33, ch);     

    foobar2(5);     

    return 0;  
}
