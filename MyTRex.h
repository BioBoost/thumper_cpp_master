#include "TRex.h"

#ifndef MY_TREX_H
#define MY_TREX_H

namespace TRexLib{

    class MyTRex: public TRex{
        public:
            /*
             * Constructor
             *
             * @i2c the I2C representing the bus on which the slave is connected.
             * @i2cAddress the address of the slave
             */
            MyTRex(I2C* i2c, int i2cAddress);

            /*
             * Read the status of the TRex controller.
             *
             * @status pointer to the StatusDataPacket that contains the values read from the controller.
             *
             * @return true if the read action was successful
             */
            bool readStatus(StatusDataPacket * status);

            /*
             * Read the RAW status of the TRex controller.
             *
             * @status buffer that will be used to store the status frame in
             * @size size of the buffer (should be big enough to store full frame)
             *
             * @return true if the read action was successful
             */
            bool readStatus(char * status, int size);

            /*
             * Write command to the TRex controller.
             *
             * @command pointer to the CommandDataPacket that contains the values that should be send to the controller.
             *
             * @return true if the write action was successful
             */
            bool writeCommand(CommandDataPacket * command);

            /*
             * Write RAW coommand frame to the TRex controller.
             *
             * @command buffer that contains the command frame that needs to be send to the TRex
             * @size size of the buffer (should be big enough to store full frame)
             *
             * @return true if the write action was successful
             */
            bool writeCommand(char * command, int size);
    };
}

#endif