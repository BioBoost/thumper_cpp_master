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
            result = i2c->read(this->i2cAddress, buffer, StatusDataPacket::SIZE_STATUS_DATA_PACKET);
            wait(0.01);
        } //while (++i < 5 && (result != StatusDataPacket::SIZE_STATUS_DATA_PACKET || buffer[STATUS_START] != 0x0F));
        while (++i < 5 && buffer[STATUS_START] != 0x0F);

        // Parse status data from the received buffer
        status->fromTRex(buffer);

        //return (result == StatusDataPacket::SIZE_STATUS_DATA_PACKET);
        return buffer[STATUS_START] == 0x0F;
    }

    /*
     * Read the RAW status of the TRex controller.
     *
     * @status buffer that will be used to store the status frame in
     * @size size of the buffer (should be big enough to store full frame)
     *
     * @return true if the read action was successful
     */
    bool MyTRex::readStatus(char * status, int size){
        if (size < StatusDataPacket::SIZE_STATUS_DATA_PACKET) {
            return false;
        }

        int i = 0;
        int result;
        do {
            result = i2c->read(this->i2cAddress, status, StatusDataPacket::SIZE_STATUS_DATA_PACKET);
            wait(0.01);
        } while (++i < 5 && status[STATUS_START] != 0x0F);

        //return (result == StatusDataPacket::SIZE_STATUS_DATA_PACKET);
        return status[STATUS_START] == 0x0F;
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

    /*
     * Write RAW coommand frame to the TRex controller.
     *
     * @command buffer that contains the command frame that needs to be send to the TRex
     * @size size of the buffer (should be big enough to store full frame)
     *
     * @return true if the write action was successful
     */
    bool MyTRex::writeCommand(char * command, int size){
        if (size < CommandDataPacket::SIZE_TREX_DATA_PACKET) {
            return false;
        }

        int result = i2c->write(this->i2cAddress, command, CommandDataPacket::SIZE_TREX_DATA_PACKET);

        return (result == 0);
    }
}