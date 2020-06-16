//    A monochrome screen is stored as a single array of bytes, allowing eight
//    consecutive pixels to be stored in one byte.The screen has width w,
//    where w is divisible by 8 (that is, no byte will be split across
//    rows).The height of the screen, of course, can be derived from the
//    length of the array and the width. Implement a function
//    drawHorizontall_ine(byte[] screen, int width, int xl, int x2, int y)
//    which draws a horizontal line from (xl, y)to(x2, y).



void draw_line (int screen[], int width, int x1, int x2, int y) {

    int start_offset = x1 % 8;
    int end_offset = x2 % 8;
    int start_byte = x1 / 8;
    int end_byte = x2 / 8;
    
    int i, index, mask;

    for (index = start_byte +1; index < end_byte ; index++) {
        int i = (width/8)*y + index;
        screen[i] = 0xff;
    }

    if (start_byte == end_byte) {
        int mask1, mask2;
        mask1 = 0xFf >> start_offset;
        mask2 = 0xFf << (8-end_offset);
        mask = mask1 & mask2;
        i = (width/8)*y + start_byte;
        screen[i] = screen[i] | mask;
        return;
    }

    i = (width/8)*y + start_byte;
    mask = 0xFf >> start_offset;
    screen[i] = screen[i] | mask;

    i = (width/8)*y + end_byte;
    mask = 0xFf << (8-end_offset);
    screen[i] = screen[i] | mask;
}
