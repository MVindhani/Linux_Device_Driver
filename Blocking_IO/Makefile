obj-m := Blocking_IO_uninterruptible.o
obj-m += Blocking_IO_interruptible.o

KERNDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KERNDIR) M=`pwd` modules

clean:
	make -C $(KERNDIR) M=`pwd` clean
