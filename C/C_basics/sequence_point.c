
#include <stdio.h>

/* 
   http://c-faq.com/expr/seqpoints.html
*/

/* 

 A sequence point is a point in time at which the dust has settled and all
 side effects which have been seen so far are guaranteed to be complete. 

 The sequence points listed in the C standard are:

 1. at the end of the evaluation of a full expression (a full expression is an
 expression statement, or any other expression which is not a subexpression
 within any larger expression); 

 2. at the ||, &&, ?:, and comma operators; and 

 at a function call (after the evaluation of all the arguments, and just
 before the actual call).  

 The Standard states that

 Between the previous and next sequence point an object shall have its stored
 value modified at most once by the evaluation of an expression. Furthermore,
 the prior value shall be accessed only to determine the value to be stored.

*/


/* This version looks reasonable, but you don't know if the right and left
 * sides of the | will each get the original version of a or if one of them
 * will get the result of the other. There's no sequence point here, so we
 * don't know anything about the order of operations here, and you may get
 * different results from the same compiler using different levels of
 * optimization.
 */

/* Cardinal sin : referencing arg a twice */
unsigned swaphalves (unsigned a) {
    a = (a >>= 16) | ( a <<= 16); 
    // a = (a >>= 16) || ( a <<= 16); /* Not useful code but sequence point is good */
    return a;
}

int main () {

    int i = 3;
    int a[10];

    // Not allowed : modify the same value twice are abominations which
    // needn't be allowed

    i = i++;
    a[i] = i++;

    // allowed
    i =  i + 1;

    unsigned ret, arg = 0x12345678;
    ret = swaphalves(arg);
    printf("arg:0x%x ret:0x%x\n", arg, ret);

    /*
      ~/Comp_lang_c/Coding/C_Coding/C_basics>gcc sequence_point.c
      ~/Comp_lang_c/Coding/C_Coding/C_basics>a.out 
      arg:0x12345678 ret:0x12340000
      ~/Comp_lang_c/Coding/C_Coding/C_basics>

    */
    return 0;
}
