#include "MyTRex.h"
#include "wait.h"

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
            wait(0.02);
        } while (++i < 5 && (result != StatusDataPacket::SIZE_STATUS_DATA_PACKET || buffer[STATUS_START] != 0x0F));

        if (i < 5) {
            // Parse status data from the received buffer
            status->fromTRex(buffer);
        }

        return (i < 5);
    }

    /*
     * Write command to the TRex controller.
     *
     * @command pointer to the CommandDataPacket that contains the values that should be send to the controller.
     *
     * @return true if the write action was successful
     */
    bool MyTRex::writeCommand(CommandDataPacket * command){
        return false;
    }
}