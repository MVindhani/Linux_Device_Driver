1. add.c:
   This module is used for the functionality of addition of 2 numbers.
2. avg.c:
   This module is used for functionality of calculating average of 2 numbers. This file uses add() from add.c file.

======================================================================================================================================

- Executing _modprobe_ command will give error first time. It means that modprobe tool is not installed.
- To install refet to the Makefile available in the repo with target _install_
- We can check the dependency variables/parameter list in the intermediate file generated while compilation _Modules Sysver_
- This dependency modules are external to Linux Source code. We can check the compiled modules in /lib/modules/<linux generic>/
- Search with ./extra. You will find add.ko and avg.ko
- While using _Modprobe_ we shall use _sudo_ and make sure that we are not loadig the module as <module_name>.ko. We should give just <module_name>
