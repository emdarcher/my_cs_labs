#test Makefile

TARGET=main
SRC=$(TARGET).cpp
CC= g++
STD=c++11
CFLAGS= -Wall --std=$(STD)
OUTPUT=$(TARGET).bin

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT)

clean:
	rm *.bin *.lst *.dmp *.hex *.elf $(OUTPUT)



