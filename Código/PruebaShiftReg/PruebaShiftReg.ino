//This example shows how to use the Mux Shield for digital outputs
#include <ShiftReg.h>
#include <Wtv020sd16p.h>

int resetPin = 2;//12;//2;  // The pin number of the reset pin.
int clockPin = 3;//A2;//3;  // The pin number of the clock pin.
int dataPin = 4;//4;  // The pin number of the data pin.
int busyPin = 5;//11;//5;  // The pin number of the busy pin.

int x;

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);
//Initialize the Mux Shield
ShiftReg shiftReg;

void setup()
{
    //Set I/O 1, I/O 2, and I/O 3 as digital outputs
    shiftReg.setMode(1,DIGITAL_OUT);  
    Serial.begin(9600);
    wtv020sd16p.reset();
    delay(100);
    wtv020sd16p.asyncPlayVoice(0);
}

int toggle = HIGH;

void loop()
{
  for (int i=0; i<12; i++)
  {
    shiftReg.digitalWriteMS(1,i,toggle);
    delay(10);
  } 
  if(toggle == HIGH)
   toggle = LOW;
  else
   toggle = HIGH; 
   
   if(Serial.available()){
     wtv020sd16p.reset();
     delay(100);
     x = Serial.parseInt();
     Serial.println(x);
     wtv020sd16p.asyncPlayVoice(x);
   }
   Serial.println(digitalRead(busyPin));
}
