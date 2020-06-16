#include <stdint.h>

int main () {

    uint8_t port = 0x5a;
    uint8_t result_8 = ( ~port ) >> 4;

    /* 
       port is first promoted to a signed int, with the following results
       port         uint8_t 0x5a
       ~port        int    0xffffffa5
       ~port >> 4   int    0x0ffffffa
       result_8	     uint8_t 0xfa
    */

    printf("result:0x%x \n", result_8);

    result_8 = (uint8_t) ~port  >> 4;
    printf("result:0x%x \n", result_8);

    return 0;
}
