obj-m := Calculator.o

KERDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KERDIR) M=`pwd` modules

clean:
	make -C $(KERDIR) M=`pwd` clean
