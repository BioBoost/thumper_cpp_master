#include <string.h>
#include "DataPacket.h"
#include "Side.h"

#ifndef TREX_COMMAND_DATA_PACKET_H
#define TREX_COMMAND_DATA_PACKET_H

namespace TRexLib{

    enum CommandDataPacketFields {
        COMMAND_START = 0,
        COMMAND_PWM_FREQ = 1,
        COMMAND_LEFT_MOTOR_SPEED_MSB = 2,
        COMMAND_LEFT_MOTOR_SPEED_LSB = 3,
        COMMAND_LEFT_MOTOR_BRAKE = 4,
        COMMAND_RIGHT_MOTOR_SPEED_MSB = 5,
        COMMAND_RIGHT_MOTOR_SPEED_LSB = 6,
        COMMAND_RIGHT_MOTOR_BRAKE = 7,
        COMMAND_SERVO_0_MSB = 8,
        COMMAND_SERVO_0_LSB = 9,
        COMMAND_SERVO_1_MSB = 10,
        COMMAND_SERVO_1_LSB = 11,
        COMMAND_SERVO_2_MSB = 12,
        COMMAND_SERVO_2_LSB = 13,
        COMMAND_SERVO_3_MSB = 14,
        COMMAND_SERVO_3_LSB = 15,
        COMMAND_SERVO_4_MSB = 16,
        COMMAND_SERVO_4_LSB = 17,
        COMMAND_SERVO_5_MSB = 18,
        COMMAND_SERVO_5_LSB = 19,
        COMMAND_ACCELEROMETER_DEVIBRATE = 20,
        COMMAND_IMPACT_SENSITIVITY_MSB = 21,
        COMMAND_IMPACT_SENSITIVITY_LSB = 22,
        COMMAND_LOW_BATTERY_MSB = 23,
        COMMAND_LOW_BATTERY_LSB = 24,
        COMMAND_I2C_ADDRESS = 25,
        COMMAND_CLOCK_FREQUENCY = 26
    };

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
            char getStartByte(void);
            PWMFrequency getPwmFrequency(void);
            int getMotorSpeed(Side side);
            bool getMotorBrake(Side side);
            int getServoPosition(int location);
            unsigned char getAcceleroMeterDevibrate(void);
            unsigned int getImpactSensitivity(void);
            unsigned int getLowBatteryVoltage(void);
            unsigned char getI2CAddress(void);
            ClockFrequency getI2CClockFrequency(void);

        /* Setters need to be accessible by all */
        public:
            void setStartByte(char start);
            void setPwmFrequency(PWMFrequency freq);
            void setMotorSpeed(Side side, int speed);
            void setMotorBrake(Side side, bool on);
            void setServoPosition(int location, int position);
            void setAcceleroMeterDevibrate(unsigned char devibrate);
            void setImpactSensitivity(unsigned int sensitivity);
            void setLowBatteryVoltage(unsigned int voltage);
            void setI2CAddress(unsigned char address);
            void setI2CClockFrequency(ClockFrequency frequency);

        /* Private member fields */
        private:
            char startbyte;
            PWMFrequency pwmFrequency;
            int leftmotorspeed;
            bool leftmotorbrake;
            int rightmotorspeed;
            bool rightmotorbrake;
            int servos[NUMBER_OF_SERVOS];
            unsigned char accelerometerDevibrate;
            unsigned int impactSensitivity;
            unsigned int lowBatteryVoltage;
            unsigned char i2cAddress;
            ClockFrequency clockFrequency;
    };
}

#endif