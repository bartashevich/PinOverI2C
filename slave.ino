#include <Wire.h>
#include <PinOverI2C.h>

#define SLAVE_ID 4

uint8_t received_op = 0;
uint8_t received_pin = 0;
uint8_t value_to_send = 0;

PinOverI2C pinI2C;

void receiveEvent(int);
void requestEvent();

void setup() {
	PinOverI2C pinI2C (SLAVE_ID, receiveEvent, requestEvent);
	Serial.begin(9600);
	Serial.println("Serial begin - slave");
}

void loop() {
  
}

void receiveEvent(int how_many){
  // read I2C data
  if(Wire.available()){
    received_op = Wire.read();
    received_pin = Wire.read();
  }

  // execute command
  if(received_op == OP_DIGITAL_OUTPUT){
    pinMode(received_pin, OUTPUT);
  }
  else if(received_op == OP_DIGITAL_INPUT){
    pinMode(received_pin, INPUT);
  }
  else if(received_op == OP_DIGITAL_WRITE_HIGH){
    digitalWrite(received_pin, HIGH);
  }
  else if(received_op == OP_DIGITAL_WRITE_LOW){
    digitalWrite(received_pin, LOW);
  }
  else if(received_op == OP_DIGITAL_READ){
    value_to_send = digitalRead(received_pin);
  }
  else if(received_op == OP_ANALOG_READ){
    value_to_send = analogRead(received_pin);
  }

  // debug
  Serial.println(received_op);
  Serial.println(received_pin);
  Serial.println();

  // reset values
  received_op = 0;
  received_pin = 0;
}

void requestEvent(){
	uint8_t to_send[2] = {(uint8_t) (value_to_send / 100), (uint8_t) (value_to_send % 100)};

	Wire.write((uint8_t *) to_send, sizeof(to_send));
}