#include "Wire.h"
#include "PinOverI2C.h"

PinOverI2C::PinOverI2C(){
	Wire.begin();
}

PinOverI2C::PinOverI2C(uint8_t address, void (*receiveEvent)(int), void (*requestEvent)(void)){
	Wire.begin(address);
	Wire.onReceive(receiveEvent);
	Wire.onRequest(requestEvent);
}

void PinOverI2C::write_i2c(uint8_t op, uint8_t pin, uint8_t slave_address){
	uint8_t to_send[this->byte_num] = {op, pin};

	Wire.beginTransmission(slave_address);
	Wire.write((uint8_t *) to_send, sizeof(to_send));
	Wire.endTransmission();

	delay(100);
}

int PinOverI2C::read_i2c(uint8_t slave_address){
	uint8_t to_receive[this->byte_num];
	// obtain registry
	Wire.requestFrom(slave_address, this->byte_num);

	if(Wire.available()){
		to_receive[0] = Wire.read();
		to_receive[1] = Wire.read();
	}

	return (int) (to_receive[0] * 100 + to_receive[1]);
}

void PinOverI2C::pinMode(uint8_t pin, uint8_t mode, uint8_t slave_address){
	if(mode == OUTPUT){
		write_i2c(OP_DIGITAL_OUTPUT, pin, slave_address);
	}
	else{
		write_i2c(OP_DIGITAL_INPUT, pin, slave_address);
	}
}

void PinOverI2C::digitalWrite(uint8_t pin, uint8_t mode, uint8_t slave_address){
	if(mode == HIGH){
		write_i2c(OP_DIGITAL_WRITE_HIGH, pin, slave_address);
	}
	else{
		write_i2c(OP_DIGITAL_WRITE_LOW, pin, slave_address);
	}
}

int PinOverI2C::digitalRead(uint8_t pin, uint8_t slave_address){
	write_i2c(OP_DIGITAL_READ, pin, slave_address);

	return read_i2c(slave_address);
}

int PinOverI2C::analogRead(uint8_t pin, uint8_t slave_address){
	write_i2c(OP_ANALOG_READ, pin, slave_address);

	return read_i2c(slave_address);
}