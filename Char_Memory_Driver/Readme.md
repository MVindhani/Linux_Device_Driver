1. CharMemory.c:
  This file is used to crearte the driver which will read and write between User Space and Kernel Space.
2. app.c:
   This file is used to read and write to & from driver.
3. Makefile:
   This file is used for compilation of driver.

=====================================================================================================
- Compile the driver
- Load the driver using $insmod command
- Create Node using $mknod command
- Compile application with $gcc app.c -o app command
- Execute ./app file to perform read and write operation.
- You can also perform read and write operation on device by using $cat and $echo command without using the app 
