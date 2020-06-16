/* 
   1. A library should ideally have only one header made public.
      Internally you could have many private header files.
 */

/* 2. Use header guards */
#ifndef _MY_PUBLIC_LIB_
#define _MY_PUBLIC_LIB_

typedef struct node_tag node_t;

/* 3. Do not put struct headers (definitions) - as the structs may change.
   Struct alignments may be different on different compilers.
   If you must, then use a version field as the first field.
   Do not use macros, your library may be called from non-C environment.
*/

node_t *allocate_s(void);
void free_s(node_t *);

/* caller doesn't have control over how things are allocated. This can be worked around by providing an API for the client to register his own allocation/deallocation functions (like SDL does)
*/

#endif
