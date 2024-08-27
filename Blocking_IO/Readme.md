1.Blocking_IO_uninterruptible.c

    This module is used to display the uninterruptible sleep wake up event for driver.

2. app.c

    This application file is used to demostrate the read and write related system programming function.

3. Makefile

    This is the make file to compile the modules

4.Blocking_IO_interruptible.c

    This module is used to display the interruptible sleep wake up event for driver.


    ===================================================================================

    First test it without app.c

    - While testing the uninterruptible.c modules, after inserting the modules and creating node, execute the read operations by executing $cat command.
    - The device will be blocked as data is not available.
    - live dmesg read buffer can be seen using command xxx (need to check )
    - Open another terminal and try to write the data using command $echo.
    - Observe that the device which was waititng for the data is unblocked now.
    = Verify the same in dmesg read buffer.