union data {
    int i;
    char c[sizeof(int)];
};

/* BIG Endian - remember crash dump ?
   low addr . . . . . . . .  . . . . . . . . . . . . . . . high addr
            0           0         0          1
            c[0]       c[1]     c[2]        c[3]  char array
            array always goes lower address to higher.
            MSB i     ...      .....       LSB i int layout
            but int 0x1 on big endian is laid out as seen above.
*/
            
void find_endian () {

    union data u;

    u.i = 1;

    if (u.c[0] == 1) {
        printf("right-to-left little-endian\n");
    } else {
        printf("left-to-right big-endian\n");
    }
    printf("&u.c[0]:%p &u.c[3]:%p &u.i:%p\n", &u.c[0], &u.c[3], &u.i);
             
}

int main (void) {

    find_endian();

    /* For an array of elements of natural types, it's always low address to high address.
     * Bit and byte ordering issues only arise when you take the bits and 
     * bytes out of the box, as it were, and line them up.
     * No issue for a char/int array as seen below.
     * But if you use an int32_t instead of char [4] for IP address for e.g.
     * then you may run into reversed IP address.
     */
    char ip_addr[4];
    printf("&ip_addr[0] = %p : &ip_addr[3] = %p\n", (void *) ip_addr, 
            (void *) &ip_addr[3]);
    /* The above will always be increasing address for both little/big endian */
    /* Also &int == &char[0] for both but lsb of int is not char[0]
       for big endian, that's the point */

    /* Remember mem dump in IOS big endian :
       0x0  00 00 00 01 00 00 00 02 00 00 00 03 00 00 00 04 
       0x10 ....
       Address at byte 3 is 0x1 that's int 0x1 but it's not char[0]
       That's the point. easy to read those 4 bytes.
     */
    return 0;
}
