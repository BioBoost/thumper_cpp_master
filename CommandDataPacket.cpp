#include "CommandDataPacket.h"

namespace TRexLib{

	char CommandDataPacket::getStartByte(void){
		return this->startbyte;
	}

	PWMFrequency CommandDataPacket::getPwmFrequency(void){
		return this->pwmFrequency;
	}

	int CommandDataPacket::getMotorSpeed(Side side){
		if (side == LEFT) {
			return this->leftmotorspeed;
		} else if (side == RIGHT){
			return this->rightmotorspeed;
		} else {
			return -1;
		}
	}

	bool CommandDataPacket::getMotorBrake(Side side){
		if (side == LEFT) {
			return this->leftmotorbrake;
		} else if (side == RIGHT){
			return this->rightmotorbrake;
		} else {
			return false;
		}
	}

	int CommandDataPacket::getServoPosition(int location){
		return this->servos[location % NUMBER_OF_SERVOS];
	}

	unsigned char CommandDataPacket::getAcceleroMeterDevibrate(void){
		return this->accelerometerDevibrate;
	}

	unsigned int CommandDataPacket::getImpactSensitivity(void){
		return this->impactSensitivity;
	}

	unsigned int CommandDataPacket::getLowBatteryVoltage(void){
		return this->lowBatteryVoltage;
	}

	unsigned char CommandDataPacket::getI2CAddress(void){
		return this->i2cAddress;
	}

	ClockFrequency CommandDataPacket::getI2CClockFrequency(void){
		return this->clockFrequency;
	}

	void CommandDataPacket::setStartByte(char start){
		this->startbyte = start;
	}

	void CommandDataPacket::setPwmFrequency(PWMFrequency freq){
		this->pwmFrequency = freq;
	}

	void CommandDataPacket::setMotorSpeed(Side side, int speed){
		if (side == LEFT) {
			this->leftmotorspeed = speed;
		} else if (side == RIGHT){
			this->rightmotorspeed = speed;
		}
	}

	void CommandDataPacket::setMotorBrake(Side side, bool on){
		if (side == LEFT) {
			this->leftmotorbrake = on;
		} else if (side == RIGHT){
			this->rightmotorbrake = on;
		}
	}

	void CommandDataPacket::setServoPosition(int location, int position){
		if (location < NUMBER_OF_SERVOS) {
			this->servos[location] = position;
		}
	}

	void CommandDataPacket::setAcceleroMeterDevibrate(unsigned char devibrate){
		this->accelerometerDevibrate = devibrate;
	}

	void CommandDataPacket::setImpactSensitivity(unsigned int sensitivity){
		this->impactSensitivity = sensitivity;
	}

	void CommandDataPacket::setLowBatteryVoltage(unsigned int voltage){
		this->lowBatteryVoltage = voltage;
	}

	void CommandDataPacket::setI2CAddress(unsigned char address){
		this->i2cAddress = address;
	}

	void CommandDataPacket::setI2CClockFrequency(ClockFrequency frequency){
		this->clockFrequency = frequency;
	}
}