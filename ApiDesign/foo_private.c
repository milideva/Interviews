#include "foo_private.h"
#include <stdlib.h>

node_t *
allocate_s (void) {
        return malloc(sizeof(node_t));
}

void free_s (node_t *node) {
        free(node);
}
