KERN_DIR = /home/book/100ask

all:
	make -C $(KERN_DIR) M='pwd' modules
	$(CROSS_COMPILE)gcc -o ledtest ledtest.c
clean:
	make -C $(KERN_DIR) M='pwd' modules clean
	rm -rf modules.order
	rm -f ledtest
#a.c b.c ==>ab.ko 
#ab-y :a.o b.o
#obj-m + = ab.0
obj-m += leddrv.o chip_demo_gpio.o board_A_led.o
