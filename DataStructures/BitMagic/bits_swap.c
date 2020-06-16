#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

typedef unsigned int uint;

static bool is_bit_set (uint *data, uint n)
{
        assert(n < (sizeof(*data) * CHAR_BIT));
        uint val = 1 << n;
        return (*data & val) ? 1 : 0;
}

static void set_bit (uint *data, uint n)
{
        *data |= (1 << n); 
}

static void clear_bit (uint *data, uint n)
{
        *data &= ~(1 << n);
}

static void swap_bits (uint *data, uint p1, uint p2)
{
        bool p1_flag = is_bit_set(data, p1);
        bool p2_flag = is_bit_set(data, p2);

        if (p1_flag) 
            set_bit(data, p2);
        else 
            clear_bit(data, p2);

        if (p2_flag)
            set_bit(data, p1);
        else 
            clear_bit(data, p1);
}

int main (void)
{
        uint data = 0x44;

        swap_bits(&data, 2, 1);
        printf("data:0x%x\n", data);

        return 0;
}

