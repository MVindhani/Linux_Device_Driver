obj-m := Kernel_Panic.o

KERNDIR =/lib/modules/`uname -r`/build

all:
	make -C $(KERNDIR) M=`pwd` modules

clean:
	make -C $(KERNDIR) M=`pwd` clean
