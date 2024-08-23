1. Calculator.c:
   This file is a driver file to create multiple driver with different minor number and same major number. It is used as calculator.

2. calc.c:
   This is a application file which is used to perform calculation.

3. Makefile:
   This is makefile to compile the driver.


   ====================================================================================================

   - Create separate devices for each add, sub, mul and div
   - Create it with proper minor number.
   - If all devices run separately then it is OK, but if they are running simultaneusly then it will not be synchronysed and hence we need to use semaphore for it.
