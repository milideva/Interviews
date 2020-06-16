/* 
   1. Right shift of signed is implementation defined.
   It moves in a 0 bit (logical) on some machines, sign bit (arithmetic) 
   on others.
   To be on safer side, always use unsigned for right shift.

   It should move in zero from right for unsigned.

   2. Left shift always moves in a 0 irrespective of type.
*/
static
unsigned int bit_count (unsigned int value) {
    unsigned int count = 0;

    unsigned int a = value;
    
    while (a) {
        if (a & 0x1) {
           count++;
        }
        a = a >> 1;
     }
    printf("value:0x%x(%d), bit_count:%d\n", value, value, count);
    return count;
}
    
int main (void) {

   bit_count(31);
   bit_count(33);
   bit_count(44);
   bit_count(63); 
   bit_count(64);
   bit_count(65);

   return 0;
}
     
