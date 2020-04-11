#include <Wire.h>
#include <PinOverI2C.h>

#define SLAVE_ID 4

PinOverI2C pinI2C;

void setup() {
  PinOverI2C pinI2C();
  Serial.begin(9600);
  Serial.println("Serial begin - master");
}

void loop() {
  pinI2C.pinMode(4, OUTPUT, SLAVE_ID);
  delay(1000);
  pinI2C.digitalWrite(4, HIGH, SLAVE_ID);
  Serial.println(pinI2C.digitalRead(4, SLAVE_ID));
  delay(1000);
  pinI2C.digitalWrite(4, LOW, SLAVE_ID);
  Serial.println(pinI2C.digitalRead(4, SLAVE_ID));
  delay(1000);
}