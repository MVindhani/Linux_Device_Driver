obj-m := Dynamic_CDD.o

KERNELDIR = /lib/modules/`uname -r`/build
all:
	make -C $(KERNELDIR) M=`pwd` modules

clean:
	make -C $(KERNELDIR) M=`pwd` clean
