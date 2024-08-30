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

    - While testing the **uninterruptible.c** modules, after inserting the modules and creating node, execute the read operations by executing $cat command.
    - The device will be blocked as data is not available.
    - live dmesg read buffer can be seen using command **$ tail -f /var/log/syslog**
    - Open another terminal and try to write the data using command $echo.
    - Observe that the device which was waititng for the data is unblocked now.
    - Verify the same in dmesg read buffer.
    - Here, when it is waiting for data to available, if you kill the process (you can get the running process id by **$ps -eaf | grep cat)** then it will not kill as it is uninterruptable wait.
    - You can kill by command **$kill -9 <process id from above command>**

    
    - While testing the **interruptible.c** modules, after inserting the modules and creating node, execute the read operations by executing $cat command.
    - The device will be blocked as data is not available.
    - live dmesg read buffer can be seen using command **$ tail -f /var/log/syslog**
    - Open another terminal and try to write the data using command $echo.
    - Observe that the device which was waititng for the data is unblocked now.
    - Verify the same in dmesg read buffer.
    - Here, when it is waiting for data to available, if you kill the process (you can get the running process id by **$ps -eaf | grep cat**) then it will kill the waitinng process as it is interruptable wait.
    - You can kill by command **$kill -9 <process id from above command>**
