ccflags-y :=-std=gnu99
obj-m := ssd1306temp_dev.o
ssd1306temp_dev-objs := ssd1306temp.o digitRenderer/digitRenderer.o i2cSend/i2cSend.o
CFLAGS = -Wno-error
#KDIR = /lib/modules/$(shell uname -r)/build
# KDIR = ~/imx-yocto-bsp/maaxboard-8ulp/build/tmp/work/maaxboard_8ulp-poky-linux/linux-imx/6.1.22+gitAUTOINC+78ce688d5a-r0/build/ 
KDIR ?= /home/madrid/imx-yocto-bsp/maaxboard-8ulp/build/tmp/work/maaxboard_8ulp-poky-linux/linux-imx/6.1.22+gitAUTOINC+78ce688d5a-r0/build
all:
	make -C $(KDIR)  M=`pwd` modules
#scp ssd1306temp_dev.ko root@192.168.10.163:/lib/modules/6.1.22+g78ce688d5a79/extra

clean:
	make -C $(KDIR)  M=`pwd` clean
