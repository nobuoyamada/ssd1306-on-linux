ccflags-y :=-std=gnu99
obj-m := ssd1306temp_dev.o
ssd1306temp_dev-objs := ssd1306temp.o digitRenderer/digitRenderer.o i2cSend/i2cSend.o
CFLAGS = -Wno-error
#KDIR = /lib/modules/$(shell uname -r)/build
KDIR = ~/imx-yocto-bsp/maaxboard-8ulp/build/tmp/work/maaxboard_8ulp-poky-linux/linux-imx/6.1.22+gitAUTOINC+78ce688d5a-r0/build/ 
all:
	make -C $(KDIR)  M=$(shell pwd) modules
 
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
