#test Makefile

TARGET=main
SRC=$(TARGET).cpp
CPPC= g++
CC= gcc
#STD= c99
STD= 
CPPSTD=c++11
CFLAGS= -Wall #--std=$(STD)
CPPFLAGS= -Wall --std=$(CPPSTD)

OUTPUT=$(TARGET).bin

all:
	$(CPPC) $(CPPFLAGS) $(SRC) -o $(OUTPUT)

c_compiler:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT)

clean:
	rm *.bin *.lst *.dmp *.hex *.elf $(OUTPUT)



