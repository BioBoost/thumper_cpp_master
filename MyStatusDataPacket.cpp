#include "MyStatusDataPacket.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

namespace TRexLib{

    /*
     * Constructor
     */
    MyStatusDataPacket::MyStatusDataPacket(void) {

    }

    /*
     * Convert the internal values to a JSON string
     *
     * @return json string
     */
    std::string MyStatusDataPacket::toJSON(void){
        StringBuffer s;
        Writer<StringBuffer> writer(s);
    
        writer.StartObject();
        
        writer.String("errors");
        writer.StartObject();
            writer.String("start_byte");
            writer.Bool(this->getErrorFlags() & 1);
            writer.String("pwm_frequency");
            writer.Bool(this->getErrorFlags() & 2);
            writer.String("motor_speed");
            writer.Bool(this->getErrorFlags() & 4);
            writer.String("servo_position");
            writer.Bool(this->getErrorFlags() & 8);
            writer.String("impact_sensitivity");
            writer.Bool(this->getErrorFlags() & 16);
            writer.String("low_battery");
            writer.Bool(this->getErrorFlags() & 32);
            writer.String("i2c_address");
            writer.Bool(this->getErrorFlags() & 64);
            writer.String("i2c_speed");
            writer.Bool(this->getErrorFlags() & 128);
        writer.EndObject();

        writer.String("battery_voltage");
        writer.Double(this->getBatteryVoltage());

        writer.String("motor_current");
        writer.StartObject();
            writer.String("left");
            writer.Double(this->getMotorCurrent(LEFT));
            writer.String("right");
            writer.Double(this->getMotorCurrent(RIGHT));
        writer.EndObject();

        writer.String("encoder_count");
        writer.StartObject();
            writer.String("left");
            writer.Uint(this->getEncoderCount(LEFT));
            writer.String("right");
            writer.Uint(this->getEncoderCount(RIGHT));
        writer.EndObject();

        writer.String("accelero_meter");
        writer.StartArray();
            writer.Uint(this->getAcceleroMeter().x);
            writer.Uint(this->getAcceleroMeter().y);
            writer.Uint(this->getAcceleroMeter().z);
        writer.EndArray();

        writer.String("impact");
        writer.StartArray();
            writer.Uint(this->getImpact().x);
            writer.Uint(this->getImpact().y);
            writer.Uint(this->getImpact().z);
        writer.EndArray();

        writer.EndObject();

        return s.GetString();
    }

    /*
     * Parse the json representation of the DataPacket
     * and set the internal values accordingly.
     *
     * @json json string representation
     */
    void MyStatusDataPacket::fromJSON(std::string json){

    }

    /*
     * Convert the internal values to a char buffer representation ready 
     * for writing to the TRex controller using I2C.
     *
     * @buffer buffer to which the values should be written (should be big enough for all values to fit)
     */
    void MyStatusDataPacket::toTRex(char * buffer){

    }

    /*
     * Parse the TRex representation of the DataPacket
     * and set the internal values accordingly.
	 *
	 * @buffer char buffer which contains the values that should be parsed
     */
    void MyStatusDataPacket::fromTRex(char * data){
    	this->setStartByte(data[STATUS_START]);
        this->setErrorFlags(data[STATUS_ERROR]);
        this->setBatteryVoltage(((data[STATUS_BATTERY_MSB] << 8) + data[STATUS_BATTERY_LSB])/100.0);   
        this->setMotorCurrent(LEFT, ((data[STATUS_LEFT_MOTOR_CURRENT_MSB] << 8) + data[STATUS_LEFT_MOTOR_CURRENT_LSB])/1000.0);
        this->setMotorCurrent(RIGHT, ((data[STATUS_RIGHT_MOTOR_CURRENT_MSB] << 8) + data[STATUS_RIGHT_MOTOR_CURRENT_LSB])/1000.0);
        this->setEncoderCount(LEFT, (data[STATUS_LEFT_ENCODER_COUNT_MSB] << 8) + data[STATUS_LEFT_ENCODER_COUNT_LSB]);
        this->setEncoderCount(RIGHT, (data[STATUS_RIGHT_ENCODER_COUNT_MSB] << 8) + data[STATUS_RIGHT_ENCODER_COUNT_LSB]);

        AcceleroMeter accel;
        accel.x = (data[STATUS_ACCELEROMETER_X_MSB] << 8) + data[STATUS_ACCELEROMETER_X_LSB];
        accel.y = (data[STATUS_ACCELEROMETER_Y_MSB] << 8) + data[STATUS_ACCELEROMETER_Y_LSB];
        accel.z = (data[STATUS_ACCELEROMETER_Z_MSB] << 8) + data[STATUS_ACCELEROMETER_Z_LSB];
        this->setAcceleroMeter(accel);

        Impact impact;
        impact.x = (data[STATUS_IMPACT_X_MSB] << 8) + data[STATUS_IMPACT_X_LSB];
        impact.y = (data[STATUS_IMPACT_Y_MSB] << 8) + data[STATUS_IMPACT_Y_LSB];
        impact.z = (data[STATUS_IMPACT_Z_MSB] << 8) + data[STATUS_IMPACT_Z_LSB];
        this->setImpact(impact);
    }
}