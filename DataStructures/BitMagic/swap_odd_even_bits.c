
/*
  Given an unsigned integer, swap all odd bits with even bits. For example, if
  the given number is 23 (00010111), it should be converted to 43
  (00101011). Every even position bit is swapped with adjacent bit on right
  side (even position bits are highlighted in binary representation of 23),
  and every odd position bit is swapped with adjacent on left side.
*/

unsigned int swap_odd_even_bits (unsigned int orig) {
    unsigned int swap, odd, even;
    int i;


    odd = orig & 0xAAaaAAaa; // 1010
    even = orig & 0x55555555; //0101
    even = even << 1;
    odd = odd >> 1; // right shift of unsigned moves in 0

    return odd | even;
}


int main()
{
    unsigned int x = 23; // 00010111

    // Output is 43 (00101011)
    printf("orig: 0x%x, swapped:0x%x \n", x, swap_odd_even_bits(x));

    x = 0xAAaaAAaa;
    printf("orig: 0x%x, swapped:0x%x \n", x, swap_odd_even_bits(x));

    return 0;
}
