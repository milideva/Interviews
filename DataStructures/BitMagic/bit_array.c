#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned long bitlist_elem_t;

typedef struct bitlist_ bitlist_t;

typedef unsigned int uint32_t;

struct bitlist_ {
    uint32_t max_elems;
    uint32_t max_bits;
    bitlist_elem_t *bits;
};

#define BITS_PER_ELEM       (sizeof(bitlist_elem_t) * CHAR_BIT)
#define BITS_TO_ELEMS(bits) (((bits)+BITS_PER_ELEM-1)/BITS_PER_ELEM)

#define BIT_TO_ELEM(bit)    ((bit)/BITS_PER_ELEM)


#define BIT_TO_BIT(bit)     ((bit)&(BITS_PER_ELEM-1))
#define BIT_TO_MASK(bit)    (1UL <<BIT_TO_BIT(bit))


bitlist_t *bitlist_alloc (uint32_t bits) 
{
    bitlist_t *bl;
    bl = calloc(1, sizeof(*bl));
    if (!bl) return bl;
    bl->bits = calloc(BITS_TO_ELEMS(bits), sizeof(*bl->bits));
    if (!bl->bits) {
        free(bl); 
        bl = NULL;
    }
    return bl;
}

bool bitlist_validbit (bitlist_t *bl, uint32_t bit)
{
    if (bit >= bl->max_bits) {
        return false;
    }
    return true;
}

void bitlist_set (bitlist_t *bl, uint32_t bit)
{
    if (bitlist_validbit(bl, bit)) {
        bl->bits[BIT_TO_ELEM(bit)] |= BIT_TO_MASK(bit);
    }
}

void bitlist_clear (bitlist_t *bl, uint32_t bit)
{    
    if (bitlist_validbit(bl, bit)) {
        bl->bits[BIT_TO_ELEM(bit)] &= ~BIT_TO_MASK(bit);
    }
}   

