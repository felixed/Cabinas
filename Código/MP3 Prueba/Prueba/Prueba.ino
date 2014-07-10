/*
 Example: Control a WTV020-SD-16P module to play voices from an Arduino board.
 Created by Diego J. Arevalo, August 6th, 2012.
 Released into the public domain.
 */

#include <Wtv020sd16p.h>

int resetPin = 13;//2;  // The pin number of the reset pin.
int clockPin = A2;//3;  // The pin number of the clock pin.
int dataPin = A3;//4;  // The pin number of the data pin.
int busyPin = 11;//5;  // The pin number of the busy pin.

/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
 */
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);
int x = 0;
void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(busyPin, INPUT);
  pinMode(resetPin, OUTPUT);
  
  digitalWrite(clockPin, HIGH);
  digitalWrite(dataPin, HIGH);
  digitalWrite(resetPin, HIGH);
  //----
  delay(1000);
  digitalWrite(clockPin, LOW);
  digitalWrite(dataPin, LOW);
  digitalWrite(resetPin, LOW);
  
  
  
  Serial.begin(9600);
  //Initializes the module.
  //delay(1000);
  wtv020sd16p.reset();
  //Plays synchronously an audio file. Busy pin is used for this method.
  wtv020sd16p.asyncPlayVoice(0);
}

void loop() {
  
  /*if(Serial.available()){
    x = Serial.parseInt();
    //Serial.println(x);
    wtv020sd16p.pauseVoice();
    wtv020sd16p.asyncPlayVoice(x);
    //Serial.println(x);
    //delay(10000);    
  }*/
  
  delay(10000);
  wtv020sd16p.asyncPlayVoice(0);
 
  

}


