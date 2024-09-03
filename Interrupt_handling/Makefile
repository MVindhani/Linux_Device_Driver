obj-m := Interrupt_1.o
obj-m += Interrupt_tasklet.o

KERNDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KERNDIR) M=`pwd` modules

clean:
	make -C $(KERNDIR) M=`pwd` clean
