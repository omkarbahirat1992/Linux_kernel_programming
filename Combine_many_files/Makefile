obj-m := init_exit_combine.o

init_exit_combine-objs := only_init.o only_exit.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
