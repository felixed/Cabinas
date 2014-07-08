#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  // put your setup code here, to run once:

}

void loop() {
  
  if(Serial.available()){
    char x = Serial.read();
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(x);        // sends five bytes
    Wire.endTransmission();    // stop transmitting
    Serial.println(x);
  }
}
