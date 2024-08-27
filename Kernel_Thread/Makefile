obj-m := Kthread.obj

KERNDIR = /lib/modules/`uname -r`/build
CUR_DIR = `pwd`

all:
	make -C $(KERNDIR) M=$(CUR_DIR) modules

clean:
	make -C $(KERNDIR) M=$(CUR_DIR) clean