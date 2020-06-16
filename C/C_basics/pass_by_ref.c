#include <stdio.h>

int add(int *a, int *b)
{
    int result = *a + *b;
    int local_a = 44444;
    int local_b = 11111;
    a = &local_a; b = &local_b;
    printf("inside %s : &a %p , &b %p\n", __FUNCTION__, &a, &b);
    /* Changing  a and b pointes do not change anything in caller, they are local arg. */
    
    return result;
}
 

int main(void)
{
  int a = 5;
  int b = 10;
  int c;

  printf("&a %p , &b %p\n", &a, &b);
  c = add(&a,&b);
  printf("a=%d, b=%d a+b=%d\n", a, b, c);
  printf("&a %p , &b %p\n", &a, &b);  
  return 0;
}

