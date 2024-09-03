1. Interrupt_1.c
    This file is used to demostrate the generation of interrupt.

2. Interrupt_tasklet.c
    This file is used to demostrate the generation of interrupt and tasklet.
    Tasklets are a deferral scheme that you can schedule for a registered function to run later. 
    The top half (the interrupt handler) performs a small amount of work, and then schedules the
    tasklet to execute later at the bottom half.

3. Makefile
    This file is used to compile the modules.