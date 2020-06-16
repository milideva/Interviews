/*
   Assigning 0 to a pointer creates a null pointer, which does not point to
   address 0, and may not be all bits 0 in its representation.
*/
#define offsetof(t,i)   ((size_t)((char *)&((t *)0)->i - (char *)0))

