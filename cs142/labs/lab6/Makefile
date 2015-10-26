#test Makefile

TARGET=main
CPPSRC=$(TARGET).cpp
SRC=$(TARGET).c
CPPC= g++
CC= gcc
STD= c99
#STD= 
CPPSTD=c++98
CFLAGS= -Wall --std=$(STD)
CPPFLAGS= -Wall --std=$(CPPSTD)

OUTPUT=$(TARGET).bin

all:
	$(CPPC) $(CPPFLAGS) $(CPPSRC) -o $(OUTPUT)

cc:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT)

clean:
	rm *.bin *.lst *.dmp *.hex *.elf $(OUTPUT)



