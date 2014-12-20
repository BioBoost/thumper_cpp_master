#include "MyTRex.h"
#include "DataPacket.h"
#include "wait.h"
#include "Log.h"

namespace TRexLib{

    /*
     * Constructor
     *
     * @i2c the I2C representing the bus on which the slave is connected.
     * @i2cAddress the address of the slave
     */
    MyTRex::MyTRex(I2C* i2c, int i2cAddress)
        : TRex(i2c, i2cAddress)
    { }

    /*
     * Read the status of the TRex controller.
     *
     * @status pointer to the StatusDataPacket that contains the values read from the controller.
     *
     * @return true if the read action was successful
     */
    bool MyTRex::readStatus(StatusDataPacket * status){
        char buffer[StatusDataPacket::SIZE_STATUS_DATA_PACKET];
        int i = 0;
        int result;
        do {
            if (i > 0) {
                Log::d("Reading status %dth time\r\n. Result = %d", i, result);
            }
            result = i2c->read(this->i2cAddress, buffer, StatusDataPacket::SIZE_STATUS_DATA_PACKET);
            wait(I2C_DELAY);
        } while (++i < I2C_RETRIES && (result != StatusDataPacket::SIZE_STATUS_DATA_PACKET || buffer[STATUS_START] != DataPacket::START_BYTE));

        if (i < I2C_RETRIES) {
            // Parse status data from the received buffer
            status->fromTRex(buffer);
        }

        return (i < I2C_RETRIES);
    }

    /*
     * Write command to the TRex controller.
     *
     * @command pointer to the CommandDataPacket that contains the values that should be send to the controller.
     *
     * @return true if the write action was successful
     */
    bool MyTRex::writeCommand(CommandDataPacket * command){
        char buffer[CommandDataPacket::SIZE_TREX_DATA_PACKET];
        int i = 0;
        int result = 0;

        // Write to TRex
        command->toTRex(buffer);
        do {
            if (i > 0) {
                Log::d("Writing command %dth time\r\n. Result = %d", i, result);
            }
            result = i2c->write(this->i2cAddress, buffer, CommandDataPacket::SIZE_TREX_DATA_PACKET);
            wait(I2C_DELAY);            
        } while (++i < I2C_RETRIES && result != CommandDataPacket::SIZE_TREX_DATA_PACKET);

        return (i < I2C_RETRIES);
    }
}