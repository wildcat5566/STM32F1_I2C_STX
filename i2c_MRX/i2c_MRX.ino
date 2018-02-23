#include <Wire.h>
int enc;
void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}
void loop() {
  Wire.requestFrom(0x4E, 3);    // request 6 bytes from slave device #8
  //Serial.println(Wire.available());
  while (Wire.available()) { // slave may send less than requested
    int c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    Serial.print(", ");
  }
  Serial.println();
  //delay(500);
}

