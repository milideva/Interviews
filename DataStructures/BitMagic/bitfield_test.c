struct S_tag
{
    unsigned int a:4;
    unsigned int b:16;

};
typedef struct S_tag s_t;

int main(void)
{
    s_t s;

    unsigned char c = 0;
    unsigned u = 0;

    s.a = s.b  = 0;

     if (s.a - 5 < 0)
         printf("s.a:%d s.a - 5 < 0\n", s.a);
     else
         printf("s.a:%d ELSE part of s.a - 5 < 0\n", s.a);
         
     if (s.b - 5 < 0)
         printf("s.b:%d s.b - 5 < 0\n", s.b);
     else
         printf("s.b:%d ELSE part of s.b - 5 < 0\n", s.b);

     if (c - 5 < 0)
         printf("c:%d c - 5 < 0\n", c);
     else
         printf("c:%d ELSE part of c - 5 < 0\n", c);

     if (u - 5 < 0)
         printf("u:%d u - 5 < 0\n", u);
     else
         printf("u:%d ELSE part of u - 5 < 0\n", u);
         
     return 0; 

} 
