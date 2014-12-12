#include "StatusDataPacket.h"

namespace TRexLib{

    /*
     * Set the start byte of the status data packet.
     *
     * @start value of the start byte
     */
    void StatusDataPacket::setStartByte(char start){
        this->startbyte = start;
    }

    /*
     * Get the start byte of the status data packet.
     *
     * @return value of the start byte
     */
    char StatusDataPacket::getStartByte(void){
        return this->startbyte;
    }

    /*
     * Set the error flags of the status data packet.
     *
     * @error value of the error flags
     */
    void StatusDataPacket::setErrorFlags(char error){
        this->errorflags = error;
    }

    /*
     * Get the error flags of the status data packet.
     *
     * @return value of the error flags byte
     */
    char StatusDataPacket::getErrorFlags(void){
        return this->errorflags;
    }

    /*
     * Set the battery voltage (in Volt) of the status data packet.
     *
     * @voltage value of the battery voltage
     */
    void StatusDataPacket::setBatteryVoltage(double voltage){
        this->batteryvoltage = voltage;
    }

    /*
     * Get the battery voltage (in Volt) of the status data packet.
     *
     * @return value of the battery voltage
     */
    double StatusDataPacket::getBatteryVoltage(void){
        return this->batteryvoltage;
    }

    /*
     * Set the current (in Ampere) of the motor on a side.
     *
     * @side the side of the H-bridge on the controller
     * @current the current in Ampere
     */
    void StatusDataPacket::setMotorCurrent(Side side, double current){
        if (side == LEFT) {
            this->leftmotorcurrent = current;
        } else if (side == RIGHT) {
            this->rightmotorcurrent = current;
        }
    }

    /*
     * Get the current (in Ampere) of the motor on a side.
     *
     * @side the side of the H-bridge on the controller
     *
     * @return the current in Ampere
     */
    double StatusDataPacket::getMotorCurrent(Side side){
        if (side == LEFT) {
            return this->leftmotorcurrent;
        } else if (side == RIGHT) {
            return this->rightmotorcurrent;
        } else return 0;
    }

    /*
     * Set the encoder count on a side.
     *
     * @side the side of the encoder on the controller
     * @count the count of the encoder
     */
    void StatusDataPacket::setEncoderCount(Side side, int count){
        if (side == LEFT) {
            this->leftencodercount = count;
        } else if (side == RIGHT) {
            this->rightencodercount = count;
        }
    }

    /*
     * Get the encoder count on a side.
     *
     * @side the side of the encoder on the controller
     *
     * @return the count of the encoder
     */
    int StatusDataPacket::getEncoderCount(Side side){
        if (side == LEFT) {
            return this->leftencodercount;
        } else if (side == RIGHT) {
            return this->rightencodercount;
        } else return 0;
    }

    /*
     * Set the accelero meter values.
     *
     * @accelero AcceleroMeter instance containing the values of the accelero meter
     */
    void StatusDataPacket::setAcceleroMeter(AcceleroMeter accelero){
        this->accelerometer = accelero;
    }

    /*
     * Get the accelero meter values.
     *
     * @return AcceleroMeter instance containing the values of the accelero meter
     */
    AcceleroMeter StatusDataPacket::getAcceleroMeter(void){
        return this->accelerometer;
    }

    /*
     * Set the accelero meter impact values.
     *
     * @impact Impact instance containing the values of the accelero meter impact
     */
    void StatusDataPacket::setImpact(Impact impact){
        this->impact = impact;
    }

    /*
     * Get the accelero meter impact values.
     *
     * @return Impact instance containing the values of the accelero meter impact
     */
    Impact StatusDataPacket::getImpact(void){
        return this->impact;
    }
}