prog: hw3.o

hw3.o: hw3.c
	gcc -c hw3.c
	gcc hw3.o -o disassembler
test:
	arm-none-eabi-as test.asm -o test.o
	arm-none-eabi-objcopy test.o -O binary --only-section=.text test.bin
	hexdump -x test.bin |sed -e 's/^[^ ]*//' > test.hex
	./disassembler < test.hex > output.txt
	diff output.txt test.asm > test.diff

clean:
	rm -rf *.o *~ test.bin test.hex output.txt test.diff
