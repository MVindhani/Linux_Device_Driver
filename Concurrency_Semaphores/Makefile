obj-m := module_one.o
obj-m += module_two.o
obj-m += Shared_var.o

KERNDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KERNDIR) M=`pwd` modules

clean:
	make -C $(KERNDIR) M=`pwd` clean
