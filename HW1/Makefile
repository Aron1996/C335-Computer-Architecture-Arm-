CC = arm-none-eabi-gcc
CFLAGS = -g -O1 -mcpu=cortex-m0 -mthumb
LDFLAGS = -g -mcpu=cortex-m0 -mthumb --specs=rdimon.specs -lc -lrdimon
AS = arm-none-eabi-as
AFLAGS = -g -mcpu=cortex-m0 -mthumb

test: HW1.elf
	qemu-system-arm  -machine versatilepb -cpu cortex-m3 -nographic -monitor null -serial null -semihosting -kernel HW1.elf

HW1.elf: test.o t1.o
	$(CC) $(LDFLAGS) test.o t1.o -o HW1.elf

test.o: test.c t1.o
	$(CC) $(CFLAGS) -c test.c

t1.o: t1.s
	$(AS) $(AFLAGS) t1.s -o t1.o

clean: 
	@rm *.o
