#include <SoftwareSerial.h>
#include <Wtv020sd16p.h>

SoftwareSerial mySerial(14, 15); // RX, TX

int resetPin = 16;  // The pin number of the reset pin.
int clockPin = 17;  // The pin number of the clock pin.
int dataPin = 18;  // The pin number of the data pin.
int busyPin = 19;  // The pin number of the busy pin.
int rutina;

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);

void setup() {
  //Initializes the module.
  wtv020sd16p.reset();
  mySerial.begin(115200);
  mySerial.println("inicio");
}
void loop() {
  
  if(mySerial.available() > 0){
  
    rutina = mySerial.read();    
            
        if (rutina == '1') {   
              wtv020sd16p.stopVoice();
              delay(100);
              mySerial.print("Secuencia 1");
              mySerial.println();    
              wtv020sd16p.playVoice(1);
        }   

        if (rutina == '2'){
              wtv020sd16p.stopVoice();
              delay(100);
              mySerial.print("Secuencia 2");
              mySerial.println();
              wtv020sd16p.playVoice(2);
        }
    
        if (rutina == '3') {
              wtv020sd16p.stopVoice();
              delay(100);
              mySerial.print("Secuencia 3");
              mySerial.println();
              wtv020sd16p.playVoice(3);
        }
        if (rutina == '4') {
              wtv020sd16p.stopVoice();
              delay(100);
              mySerial.print("Secuencia 4");
              mySerial.println();
              wtv020sd16p.playVoice(4);
        }
        if (rutina == '5') {
              wtv020sd16p.stopVoice();
              delay(100);
              mySerial.print("Secuencia 5");
              mySerial.println();
              wtv020sd16p.playVoice(5);
        }
        if (rutina == '6') {
              wtv020sd16p.stopVoice();
              delay(100);
              mySerial.print("Secuencia 6");
              mySerial.println();
              wtv020sd16p.playVoice(6);
        }
  }     
}        
