PWD := $(shell pwd)
KDIR = /lib/modules/$(shell uname -r)/build

MODULE_NAME = fp_perf
obj-m := $(MODULE_NAME).o
ccflags-y := -O0 -Wall -std=gnu99  -msse2

all: clean int_perf fp_perf
	gnuplot plot.gp

int_perf:
	$(MAKE) -C $(KDIR) M=$(PWD) modules EXTRA_CFLAGS='-DINT -DOPERATION=\"INTEGER\"'
	$(MAKE) run
	dmesg -f kern | cut -d ' ' -f 2- >> integer.out
fp_perf:
	$(MAKE) -C $(KDIR) M=$(PWD) modules EXTRA_CFLAGS='-DFP -DOPERATION=\"FLOAT\"'
	$(MAKE) run
	dmesg -f kern | cut -d ' ' -f 2- >> float.out

run:
	-$(MAKE) unload
	sudo dmesg -C
	$(MAKE) load
	$(MAKE) unload

load:
	sudo insmod $(MODULE_NAME).ko
unload:
	sudo rmmod $(MODULE_NAME).ko
clean:
	sudo dmesg -C
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	$(RM) *.out compare.png