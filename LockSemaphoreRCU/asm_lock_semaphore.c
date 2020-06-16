typedef unsigned long ulong;

int lock_semaphore (int *sem)
{
    ulong sem_value, temp;
    int result;

    asm volatile ("
        .set noreorder
     0: ll      %0,0(%3)        # load-linked the sem (into return reg)
        li      %2,1            # load 0x01 into register
        sc      %2,0(%3)        # store conditionally to sem
        beq     %2,$0,0b        # was the ll <-> sc atomic
        nop                     # branch delay
        bne     %0,$0,1f        # did we get the semaphore?
        move    %1,$0           # no, setup FALSE return value (bd slot)
        li      %1,1            # yes, setup TRUE return value
     1:
        .set reorder"
                  : "=&r"(sem_value), "=r"(result),     /* outputs */
                    "=r"(temp) /* not really output, but gcc complains */
                  : "r" (sem));                         /* inputs  */
    return(result);
}

