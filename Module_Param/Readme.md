1. mod_param.c:
   This file is used to take the input parameter from the user via command line.
   It will take value of one integer parameter.

2. mod_param_print.c:
   This file is used to take the input input parameter from the user via command line.
   It is take string as parameter and number of iterations.

3. Makefile:
   This file is used to compile the code.

   ==============================================================================

   - Compile the code and load the driver using $insmod command
   - It will take the value mentioned in the source file.
   - Check the output in $dmesg.
   - Remove the driver.
   - Load the module again but this time pass the parameter along with $insmod command as follow:
      $sudo insmod Module_Param.ko temp = 50 // for Module_Param.c file
      $sudo insmod Module_Param_Print.ko what=Kernel repeat=5 // for Module_Param_Print file
   - Check the output in $dmesg.
