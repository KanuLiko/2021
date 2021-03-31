PREFIX=arm-linux-gnueabihf-
CC=$(PREFIX)gcc
LD=$(PREFIX)ld 
AR=$(PREFIX)ar 
OBJCOPY=$(PREFIX)objcopy

CPPFLAGS :=
ASFLAGS := -nostdlib -static -g 
CCFLAGS := $(ASFLAGS)

target-imx = fastcpu.imx
target-img := $(basename $(target-imx)).img 
target-elf := $(basename $(target-imx)).elf
target := $(target-imx) $(target-img) $(target-elf)

objs := start.o main.o pll.o switcher.o clkroot.o led.o
deps := $(patsubst %.o,%.d,$(objs))

all:$(target)
download: $(target)
	sudo ./tool/uuu $(target-imx)
$(target-elf):$(objs)
	$(LD) -o $@ -T imx6ull.lds -g $(objs) \
	-L/usr/local/arm/gcc-linaro-6.2.1-2016.11-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/6.2.1 \
	-L/usr/lib/gcc/x86_64-linux-gnu/7 \
	-lgcc
%.bin:%.elf
	$(OBJCOPY) -O binary -S $< $*.bin 
%.imx:%.bin 
	./tools/mkimage -n ./tools/imximage.cfg.cfgtmp -T imximage \
	-e 0x80100000 -d $< $@
%.img:%.imx
	dd if=/dev/zero of=1k.bin bs=1024 count=1
	cat 1k.bin $< >$@ 
%.o:%.S
	$(CC) -c $(ASFLAGS) -o $@ $< -std=c99
%.o:%.c
	$(CC) -c $(ASFLAGS) -o $@ $< -std=c99 
%.d:%.s
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.$$$$

include $(deps)
clean:
	rm -f $(target) $(objs) 1k.bin
.PHONY: all clean download
