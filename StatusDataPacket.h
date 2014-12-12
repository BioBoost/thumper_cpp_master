#include "DataPacket.h"
#include "Side.h"
#include "AcceleroMeter.h"

#ifndef TREX_STATUS_DATA_PACKET_H
#define TREX_STATUS_DATA_PACKET_H

namespace TRexLib{

    enum StatusDataPacketFields {
        STATUS_START = 0,
        STATUS_ERROR = 1,
        STATUS_BATTERY_MSB = 2,
        STATUS_BATTERY_LSB = 3,
        STATUS_LEFT_MOTOR_CURRENT_MSB = 4,
        STATUS_LEFT_MOTOR_CURRENT_LSB = 5,
        STATUS_LEFT_ENCODER_COUNT_MSB = 6,
        STATUS_LEFT_ENCODER_COUNT_LSB = 7,
        STATUS_RIGHT_MOTOR_CURRENT_MSB = 8,
        STATUS_RIGHT_MOTOR_CURRENT_LSB = 9,
        STATUS_RIGHT_ENCODER_COUNT_MSB = 10,
        STATUS_RIGHT_ENCODER_COUNT_LSB = 11,
        STATUS_ACCELEROMETER_X_MSB = 12,
        STATUS_ACCELEROMETER_X_LSB = 13,
        STATUS_ACCELEROMETER_Y_MSB = 14,
        STATUS_ACCELEROMETER_Y_LSB = 15,
        STATUS_ACCELEROMETER_Z_MSB = 16,
        STATUS_ACCELEROMETER_Z_LSB = 17,
        STATUS_IMPACT_X_MSB = 18,
        STATUS_IMPACT_X_LSB = 19,
        STATUS_IMPACT_Y_MSB = 20,
        STATUS_IMPACT_Y_LSB = 21,
        STATUS_IMPACT_Z_MSB = 22,
        STATUS_IMPACT_Z_LSB = 23
    };

    class StatusDataPacket: public DataPacket{
        public:
            /* Number of bytes in the TREX byte array representation */
            const static int SIZE_STATUS_DATA_PACKET = 24;

        /* Setters are only needed internally so we set them protected */
        protected:
            /*
             * Set the start byte of the status data packet.
             *
             * @start value of the start byte
             */
            void setStartByte(char start);

            /*
             * Set the error flags of the status data packet.
             *
             * @error value of the error flags
             */
            void setErrorFlags(char error);

            /*
             * Set the battery voltage (in Volt) of the status data packet.
             *
             * @voltage value of the battery voltage
             */
            void setBatteryVoltage(double voltage);

            /*
             * Set the current (in Ampere) of the motor on a side.
             *
             * @side the side of the H-bridge on the controller
             * @current the current in Ampere
             */
            void setMotorCurrent(Side side, double current);

            /*
             * Set the encoder count on a side.
             *
             * @side the side of the encoder on the controller
             * @count the count of the encoder
             */
            void setEncoderCount(Side side, int count);

            /*
             * Set the accelero meter values.
             *
             * @accelero AcceleroMeter instance containing the values of the accelero meter
             */
            void setAcceleroMeter(AcceleroMeter accelero);

            /*
             * Set the accelero meter impact values.
             *
             * @impact Impact instance containing the values of the accelero meter impact
             */
            void setImpact(Impact impact);

        /* Getters need to be accessible by all */
        public:
            /*
             * Get the start byte of the status data packet.
             *
             * @return value of the start byte
             */
            char getStartByte(void);

            /*
             * Get the error flags of the status data packet.
             *
             * @return value of the error flags byte
             */
            char getErrorFlags(void);

            /*
             * Get the battery voltage (in Volt) of the status data packet.
             *
             * @return value of the battery voltage
             */
            double getBatteryVoltage(void);

            /*
             * Get the current (in Ampere) of the motor on a side.
             *
             * @side the side of the H-bridge on the controller
             *
             * @return the current in Ampere
             */
            double getMotorCurrent(Side side);

            /*
             * Get the encoder count on a side.
             *
             * @side the side of the encoder on the controller
             *
             * @return the count of the encoder
             */
            int getEncoderCount(Side side);

            /*
             * Get the accelero meter values.
             *
             * @return AcceleroMeter instance containing the values of the accelero meter
             */
            AcceleroMeter getAcceleroMeter(void);

            /*
             * Get the accelero meter impact values.
             *
             * @return Impact instance containing the values of the accelero meter impact
             */
            Impact getImpact(void);

        /* Private member fields */
        private:
            char startbyte;
            char errorflags;
            double batteryvoltage;
            double leftmotorcurrent;
            double rightmotorcurrent;
            int leftencodercount;
            int rightencodercount;
            AcceleroMeter accelerometer;
            Impact impact;
    };
}

#endif