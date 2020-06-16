
#include <stdio.h>

/*
  The usual arithmetic conversions are rules that provide a mechanism to yield
  a common type when both operands of a binary operator are balanced to a
  common type or the second and third operands of the conditional operator ( ? 
  : ) are balanced to a common type. Conversions involve two operands of
  different types, and one or both operands may be converted. Many operators
  that accept arithmetic operands perform conversions using the usual
  arithmetic conversions. **After integer promotions** are performed on both
  operands, the following rules are applied to the promoted operands:

    If both operands have the same type, no further conversion is needed.

    If both operands are of the same integer type (signed or unsigned), the
    operand with the type of lesser integer conversion rank is converted to
    the type of the operand with greater rank.

    If the operand that has unsigned integer type has rank greater than or
    equal to the rank of the type of the other operand, the operand with
    signed integer type is converted to the type of the operand with unsigned
    integer type.

    If the type of the operand with signed integer type can represent all of
    the values of the type of the operand with unsigned integer type, the
    operand with unsigned integer type is converted to the type of the operand
    with signed integer type.

    Otherwise, both operands are converted to the unsigned integer type
    corresponding to the type of the operand with signed integer
    type. Specific operations can add to or modify the semantics of the usual
    arithmetic operations.
*/

int main () {
    int si = -1;
    unsigned int ui = 1;

    printf("Is -1 in int < 1 in unsigned int  ?? ans: %d\n", si < ui);

    printf("Fixed it with typecasting unsigned to int!! Now ans: %d\n", 
           si < (int)ui);

    return 0;
}
