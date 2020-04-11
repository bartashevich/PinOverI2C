#ifndef PinOverI2C_h
#define PinOverI2C_h
#include "Arduino.h"

#define OP_DIGITAL_OUTPUT 0x1
#define OP_DIGITAL_INPUT 0x2
#define OP_DIGITAL_WRITE_HIGH 0x3
#define OP_DIGITAL_WRITE_LOW 0x4
#define OP_DIGITAL_READ 0x5
#define OP_ANALOG_READ 0x6

class PinOverI2C {
	public:
		PinOverI2C();
		PinOverI2C(uint8_t address, void (*receiveEvent)(int), void (*requestEvent)(void));
		void Master();
		void write_i2c(uint8_t op, uint8_t pin, uint8_t slave_address);
		int read_i2c(uint8_t slave_address);
		void pinMode(uint8_t pin, uint8_t mode, uint8_t slave_address);
		void digitalWrite(uint8_t pin, uint8_t mode, uint8_t slave_address);
		int digitalRead(uint8_t pin, uint8_t slave_address);
		int analogRead(uint8_t pin, uint8_t slave_address);

	private:
		uint8_t byte_num = 2;
};

#endif