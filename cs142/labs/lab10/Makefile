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
#have it include all .h files in current directory
CPPFLAGS+= -I. 

LOCAL_CPPSRC= Property.cpp Commercial.cpp Residential.cpp

CPPSRC+= $(LOCAL_CPPSRC)

OUTPUT=$(TARGET).bin

all:
	$(CPPC) $(CPPFLAGS) $(CPPSRC) -o $(OUTPUT)

cc:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT)

clean:
	rm *.bin *.lst *.dmp *.hex *.elf $(OUTPUT)



