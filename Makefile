# The compiler
BINPATH=/home/nico/buildroot/output/host/usr/bin/arm-buildroot-linux-uclibcgnueabi-
# CC=$(BINPATH)g++
CC=g++

# Compiler flags
CFLAGS  = -Wall -Wno-write-strings -O
  #  -Wall turns on most, but not all, compiler warnings
  # -Wno-write-strings suppresses warning: deprecated conversion from string constant to ‘char*’
  # -O because of the use of inline functions, you *have* to use '-O' or some variation when you compile your program! (source: http://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/tree/Documentation/i2c/dev-interface)


all: clean I2C.o MyI2C.o wait.o Serial.o StatusDataPacket.o CommandDataPacket.o MyStatusDataPacket.o MyCommandDataPacket.o TRex.o MyTRex.o TcpDaemon.o main.o 
	$(CC) $(CFLAGS) I2C.o MyI2C.o wait.o Serial.o StatusDataPacket.o CommandDataPacket.o MyStatusDataPacket.o MyCommandDataPacket.o TRex.o MyTRex.o TcpDaemon.o main.o -o i2c_pi_trex_master

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

CommandDataPacket.o: CommandDataPacket.cpp
	$(CC) -c $(CFLAGS) CommandDataPacket.cpp

MyStatusDataPacket.o: MyStatusDataPacket.cpp
	$(CC) -c $(CFLAGS) MyStatusDataPacket.cpp

MyCommandDataPacket.o: MyCommandDataPacket.cpp
	$(CC) -c $(CFLAGS) MyCommandDataPacket.cpp

TRex.o: TRex.cpp
	$(CC) -c $(CFLAGS) TRex.cpp

MyTRex.o: MyTRex.cpp
	$(CC) -c $(CFLAGS) MyTRex.cpp

TcpDaemon.o: TcpDaemon.cpp
	$(CC) -c $(CFLAGS) TcpDaemon.cpp

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp

clean:
	rm -f *.o i2c_pi_trex_master