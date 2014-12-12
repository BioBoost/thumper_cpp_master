# The compiler
BINPATH=/home/nico/buildroot/output/host/usr/bin/arm-buildroot-linux-uclibcgnueabi-
# CC=$(BINPATH)g++
CC=g++

# Compiler flags
CFLAGS  = -Wall
  #  -Wall turns on most, but not all, compiler warnings


all: clean I2C.o MyI2C.o wait.o Serial.o StatusDataPacket.o MyStatusDataPacket.o TRex.o MyTRex.o main.o 
	$(CC) $(CFLAGS) I2C.o MyI2C.o wait.o Serial.o StatusDataPacket.o MyStatusDataPacket.o TRex.o MyTRex.o main.o -o i2c_pi_trex_master

I2C.o: I2C.cpp
	$(CC) -c $(CFLAGS) I2C.cpp

MyI2C.o: MyI2C.cpp
	$(CC) -c $(CFLAGS) MyI2C.cpp

wait.o: wait.cpp
	$(CC) -c $(CFLAGS) wait.cpp

Serial.o: Serial.cpp
	$(CC) -c $(CFLAGS) Serial.cpp

StatusDataPacket.o: StatusDataPacket.cpp
	$(CC) -c $(CFLAGS) StatusDataPacket.cpp

MyStatusDataPacket.o: MyStatusDataPacket.cpp
	$(CC) -c $(CFLAGS) MyStatusDataPacket.cpp

TRex.o: TRex.cpp
	$(CC) -c $(CFLAGS) TRex.cpp

MyTRex.o: MyTRex.cpp
	$(CC) -c $(CFLAGS) MyTRex.cpp

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp

clean:
	rm -f *.o i2c_pi_trex_master