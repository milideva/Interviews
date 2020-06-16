/* 
   Try to compile gcc.c4.5.3-p0 -O2 strict_alias.c
   
   http://stackoverflow.com/questions/98650/what-is-the-strict-aliasing-rule

   Type-punning and strict-aliasing
   http://blog.qt.digia.com/blog/2011/06/10/type-punning-and-strict-aliasing/
   http://dbp-consulting.com/StrictAliasing.pdf


   "Strict aliasing is an assumption, made by the C (or C++) compiler, that dereferencing pointers to objects of different types will never refer to the same memory location (i.e. alias each other.)"

   So basically if you have an int* pointing to some memory containing an int and then you point a float* to that memory and use it as a float you break the rule. If your code does not respect this, then the compiler's optimizer will most likely break your code.

   The exception to the rule is a char*, which is allowed to point to any type.

   ***** So how do I get around this? *****

   1. Use a union. Most compilers support this without complaining about strict aliasing. This is allowed in C99 and explicitly allowed in C11.

    union {
          Msg msg;
          unsigned int asBuffer[sizeof(Msg)];
    };
                                   
    2. You can disable strict aliasing in your compiler (f[no-]strict-aliasing in gcc))

    3. You can use char* for aliasing instead of your system's word. The rules allow an exception for char* (including signed char and unsigned char). It's always assumed that char* aliases other types. However this won't work the other way: there's no assumption that your struct aliases a buffer of chars.


*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    struct _node *next;
    int value;
} Node;

int main (int argc, char **argv)
{
    Node *list, *node, *tail;
    int i;
    
    list = NULL;
    tail = (Node *) &list; //WTF
    
    for (i = 0; i < 10; i++) {
        node = malloc(sizeof (Node));
        node->next = NULL;
        node->value = i;
        
        tail->next = node;
        tail = node;
    }
    
    if (list == NULL) {
        printf ("oops, list is null???\n");
    } else {
        printf ("list is allocated\n");
    }
    return 0;
}

