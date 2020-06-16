#include <limits.h>
#include <stdio.h>
#include <stdbool.h>


static bool check_pos (unsigned int i, unsigned int pos) {
    unsigned max_bits = (sizeof(i) * CHAR_BIT);
    if (pos >= max_bits) {
        /* Put an error message here */
        return false;
    }
    return true;
}

static bool is_bit_set (unsigned int i, unsigned int pos) {
    if (!check_pos(i,pos)) return false;

    if (i & (1 << pos)) return true;

    return false;
}

static bool set_bit (unsigned int *data, unsigned int pos) {

    if (!check_pos(*data,pos)) return false;

    *data |= (0x1 << pos);

    return true;
}

static bool clear_bit (unsigned int *data, unsigned int pos) {

    if (!check_pos(*data, pos)) return false;

    *data &= ~(0x1 << pos);

    return true;
}

static bool unset_bit (unsigned int *data, unsigned int pos) {
    return clear_bit(data, pos);
}

static bool is_bit_clear (unsigned int i, unsigned int pos) {
    if (!check_pos(i,pos)) return false;

    return !is_bit_set(i, pos);
}
