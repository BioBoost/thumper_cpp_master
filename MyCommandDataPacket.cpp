#include "MyCommandDataPacket.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <sstream>

using namespace rapidjson;

namespace TRexLib{

    /*
     * Constructor
     */
    MyCommandDataPacket::MyCommandDataPacket(void) { }

    /*
     * Convert the internal values to a JSON string
     *
     * @return json string
     */
    std::string MyCommandDataPacket::toJSON(void) {
        StringBuffer s;
        Writer<StringBuffer> writer(s);
    
        writer.StartObject();
        writer.String("pwm_frequency");
        writer.Uint(this->getPwmFrequency());

        writer.String("motor_speed");
        writer.StartObject();
            writer.String("left");
            writer.Int(this->getMotorSpeed(LEFT));
            writer.String("right");
            writer.Int(this->getMotorSpeed(RIGHT));
        writer.EndObject();

        writer.String("brake");
        writer.StartObject();
            writer.String("left");
            writer.Bool(this->getMotorBrake(LEFT));
            writer.String("right");
            writer.Bool(this->getMotorBrake(RIGHT));
        writer.EndObject();

        writer.String("servos");
        writer.StartArray();
            for (int i = 0; i < NUMBER_OF_SERVOS; i++) {
                writer.Int(this->getServoPosition(i));
            }
        writer.EndArray();

        writer.String("accelero_meter_devibrate");
        writer.Uint(this->getAcceleroMeterDevibrate());

        writer.String("impact_sensitivity");
        writer.Uint(this->getImpactSensitivity());

        writer.String("low_battery_voltage");
        writer.Uint(this->getLowBatteryVoltage());

        writer.String("i2c_slave_address");
        writer.Uint(this->getI2CAddress());

        writer.String("clock_frequency");
        writer.Uint(this->getI2CClockFrequency());

        writer.EndObject();

        return s.GetString();
    }

    /*
     * Parse the json representation of the DataPacket
     * and set the internal values accordingly.
     *
     * @json json string representation
     */
    void MyCommandDataPacket::fromJSON(std::string json) {
        // Parse the json string
        Document doc;
        doc.Parse(json.c_str());

        // Set the startbyte
        setStartByte(0x0F);

        // Set the PWM freq
        PWMFrequency freq = (PWMFrequency)(doc["pwm_frequency"].GetInt());
        setPwmFrequency(freq);

        // Set motor speeds
        int speed = doc["motor_speed"]["left"].GetInt();
        setMotorSpeed(LEFT, speed);
        speed = doc["motor_speed"]["right"].GetInt();
        setMotorSpeed(RIGHT, speed);

        // Set motor brakes
        bool brake = doc["brake"]["left"].GetBool();
        setMotorBrake(LEFT, brake);
        brake = doc["brake"]["right"].GetBool();
        setMotorBrake(RIGHT, brake);

        // Set servos
        const Value& servoValues = doc["servos"];
        for (int i = 0; i < NUMBER_OF_SERVOS; i++) {
            int pos = servoValues[i].GetInt();
            setServoPosition(i, pos);
        }

        // Set accelero devibrate
        unsigned char acceldevib = (unsigned char)(doc["accelero_meter_devibrate"].GetInt());
        setAcceleroMeterDevibrate(acceldevib);

        // Set impact sensitivity
        unsigned int sensitivity = doc["impact_sensitivity"].GetInt();
        setImpactSensitivity(sensitivity);

        // Set low battery voltage
        unsigned int volt = doc["low_battery_voltage"].GetInt();
        setLowBatteryVoltage(volt);

        // Set i2c slave address
        unsigned char i2cslaveaddress = (unsigned char)(doc["i2c_slave_address"].GetInt());
        setI2CAddress(i2cslaveaddress);

        // Set i2c clock frequency
        ClockFrequency clockfreq = (ClockFrequency)(doc["clock_frequency"].GetInt());
        setI2CClockFrequency(clockfreq);
    }

    /*
     * Convert the internal values to a char buffer representation ready 
     * for writing to the TRex controller using I2C.
     *
     * @buffer buffer to which the values should be written (should be big enough for all values to fit)
     */
    void MyCommandDataPacket::toTRex(char * buffer) {

        buffer[COMMAND_START] = this->getStartByte();
        buffer[COMMAND_PWM_FREQ] = this->getPwmFrequency();

        buffer[COMMAND_LEFT_MOTOR_SPEED_MSB] = (this->getMotorSpeed(LEFT) / 256);
        buffer[COMMAND_LEFT_MOTOR_SPEED_LSB] = (this->getMotorSpeed(LEFT) % 256);
        buffer[COMMAND_LEFT_MOTOR_BRAKE] = getMotorBrake(LEFT);

        buffer[COMMAND_RIGHT_MOTOR_SPEED_MSB] = (this->getMotorSpeed(RIGHT) / 256);
        buffer[COMMAND_RIGHT_MOTOR_SPEED_LSB] = (this->getMotorSpeed(RIGHT) % 256);
        buffer[COMMAND_RIGHT_MOTOR_BRAKE] = getMotorBrake(RIGHT);

        for (int i = 0; i < NUMBER_OF_SERVOS; i++) {
            buffer[COMMAND_SERVO_0_MSB+2*i] = (this->getServoPosition(i) / 256);
            buffer[COMMAND_SERVO_0_LSB+2*i] = (this->getServoPosition(i) % 256); 
        }

        buffer[COMMAND_ACCELEROMETER_DEVIBRATE] = this->getAcceleroMeterDevibrate();

        buffer[COMMAND_IMPACT_SENSITIVITY_MSB] = (this->getImpactSensitivity() / 256);
        buffer[COMMAND_IMPACT_SENSITIVITY_LSB] = (this->getImpactSensitivity() % 256);

        buffer[COMMAND_LOW_BATTERY_MSB] = (this->getLowBatteryVoltage() / 256);
        buffer[COMMAND_LOW_BATTERY_LSB] = (this->getLowBatteryVoltage() % 256);

        buffer[COMMAND_I2C_ADDRESS] = this->getI2CAddress();
        buffer[COMMAND_CLOCK_FREQUENCY] = this->getI2CClockFrequency();
    }

    /*
     * Parse the TRex representation of the DataPacket
     * and set the internal values accordingly.
	 *
	 * @buffer char buffer which contains the values that should be parsed
     */
    void MyCommandDataPacket::fromTRex(char * data) { }
}