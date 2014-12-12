#include <string.h>
#include "Side.h"

#ifndef TREX_COMMAND_DATA_PACKET_H
#define TREX_COMMAND_DATA_PACKET_H

namespace TRexLib{

    /*
     * Possible PWN frequencies for the motor control.
     */
    enum PWMFrequency {
        PWMF_31250HZ, PWMF_3906HZ, PWMF_977HZ, PWMF_488HZ, PWMF_244HZ, PWMF_122HZ, PWMF_31HZ
    };

    /*
     * Possible I2C frequencies.
     */
    enum ClockFrequency { CF_100KHZ, CF_400KHZ };

    class CommandDataPacket: public DataPacket{
        public:
            /* Number of bytes in the TREX byte array representation */
            const static int SIZE_TREX_DATA_PACKET = 27;

            /* Number of servos the system can control */
            const static int NUMBER_OF_SERVOS = 6;

        /* Getters are only needed internally so we set them protected */
        protected:
            // virtual unsigned char getStartByte(void) = 0;
            // virtual PWMFrequency getPwmFrequency(void) = 0;
            // virtual int getMotorSpeed(Side side) = 0;
            // virtual bool getMotorBrake(Side side) = 0;
            // virtual int getServoPosition(int location) = 0;
            // virtual unsigned char getAcceleroMeterDevibrate(void) = 0;
            // virtual unsigned char getImpactSensitivity(void) = 0;
            // virtual int getLowBatteryVoltage(void) = 0;
            // virtual unsigned char getI2CAddress(void) = 0;
            // virtual ClockFrequency getI2CClockFrequency(void) = 0;

        /* Setters need to be accessible by all */
        public:
            // virtual void setStartByte(char start) = 0;
            // virtual void setPwmFrequency(PWMFrequency freq) = 0;
            // virtual void setMotorSpeed(Side side, int speed) = 0;
            // virtual void setMotorBrake(Side side, bool on) = 0;
            // virtual void setServoPosition(int location, int position) = 0;
            // virtual void setAcceleroMeterDevibrate(unsigned char devibrate) = 0;
            // virtual void setLowBatteryVoltage(int sensitivity) = 0;
            // virtual void setI2CAddress(unsigned char address) = 0;
            // virtual void setI2CClockFrequency(ClockFrequency frequency) = 0;
    };
}

#endif