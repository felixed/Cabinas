#include <SoftwareSerial.h>
#include <Wtv020sd16p.h> //Librería del MP3
#include <Wire.h>
#include <ShiftReg.h>
#include "Const_seq.h"
#include "Seq.h"

extern int const seq1[20];
extern int const seq2[20];
extern int const seq3[20];

// ---- MP3 Pins ---
int resetPin = 20;   // The pin number of the reset pin.
int clockPin = 21;   // The pin number of the clock pin.
int dataPin = 17;    // The pin number of the data pin.
int busyPin = 16;    // The pin number of the busy pin
   
int n;               // Variable auxiliar para determinar pin de salida del Arduino
int rutina;          // Número de rutina
int secuencia[20];   // Matriz de transferencia/copia de secuencias
int leerparo;        // Variable auxiliar para disparar paro
int paro;            // Variable que identifica si se precionó la tecla/botón paro


Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin); //Se declara el modulo MP3
SoftwareSerial mySerial(14, 15); // RX, TX
bool I2C = false;
ShiftReg shiftReg;

void setup(){
  //Initializes the module.
  wtv020sd16p.reset();
  
  for(int i=2; i < 14;i++){
  
   pinMode(i, OUTPUT);
    
  } 
  mySerial.begin(115200);
  mySerial.println("inicio");
  Serial.begin(9600);
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  
}

void receiveEvent(int howMany)
{
  int x = Wire.read();
    if(x == 'x')
      paro = x;
    else
      rutina = x;
  Serial.println("Wire!!");
  Serial.println(x);
  I2C = true;
}

void loop(){   

  if(mySerial.available() > 0 || Serial.available() || I2C){
    
    //rutina = mySerial.read();    
    if(!I2C)
      rutina = Serial.read();
    else
      Serial.println("I2C");
    I2C = false;  
    Serial.print("La rutina es: ");
    Serial.println(rutina);
        if (rutina == '1') {
              paro=0;
              Serial.print("Secuencia 1");
              Serial.println();    
              wtv020sd16p.playVoice(0); // Comentario temporal
              for(int i=0; i < 20;i++){
                secuencia[i]=seq1[i];
              }
              leerbit();
        }   

        if (rutina == '2'){
              paro=0;
              mySerial.print("Secuencia 2");
              mySerial.println();    
              wtv020sd16p.playVoice(0); // Comentario temporal
              for(int i=0; i < 20;i++){
                secuencia[i]=seq1[i];
              }
              leerbit();
        }
    
        if (rutina == '3') {
              paro=0;
              mySerial.print("Secuencia 3");
              mySerial.println();    
              wtv020sd16p.playVoice(0); // Comentario temporal
              for(int i=0; i < 20;i++){
                secuencia[i]=seq1[i];
              }
              leerbit();
        }
        if (rutina == '4') {
              paro=0;
              mySerial.print("Secuencia 4");
              mySerial.println();
              wtv020sd16p.playVoice(4); // Comentario temporal
              for(int i=0; i < 20;i++){
                secuencia[i]=seq1[i];
              }
              for(int i=0; i < 3;i++){
                leerbit();
              }
        }
        if (rutina == '5') {
              paro=0;
              mySerial.print("Secuencia 5");
              mySerial.println();
              wtv020sd16p.playVoice(4); // Comentario temporal
              for(int i=0; i < 20;i++){
                secuencia[i]=seq2[i];
              }
              for(int i=0; i < 3;i++){
                leerbit();
              }
        }
        if (rutina == '6') {
              paro=0;
              mySerial.print("Secuencia 6");
              mySerial.println();
              wtv020sd16p.playVoice(4); // Comentario temporal
              for(int i=0; i < 20;i++){
                secuencia[i]=seq3[i];
              }
              for(int i=0; i < 3;i++){
                leerbit();
              }
        }
        if (rutina == '7') { //Red
          if(!paro){
            leerparo = mySerial.read();    
            if(leerparo == 'x'){
                paro=1;
            }
            for(int i=4; i < 14; i=i+3){
              if(digitalRead(i) == LOW){
                digitalWrite(i,HIGH);
              }
              else{
                digitalWrite(i,LOW);
              }  
            }
          }
          paro=0;  
        }
        if (rutina == '8') { //Blue
          if(!paro){
            leerparo = mySerial.read();    
            if(leerparo == 'x'){
                paro=1;
            }
            for(int i=3; i < 14; i=i+3){
              if(digitalRead(i) == LOW){
                digitalWrite(i,HIGH);
              }
              else{
                digitalWrite(i,LOW);
              } 
            }
          }
          paro=0;  
        }
        if (rutina == '9') { //Green
          if(!paro){
            leerparo = mySerial.read();    
            if(leerparo == 'x'){
                paro=1;
            }
            for(int i=2; i < 14; i=i+3){
              if(digitalRead(i) == LOW){
                digitalWrite(i,HIGH);
              }
              else{
                digitalWrite(i,LOW);
              } 
            }
          }
          paro=0; 
        }
        
        I2C = false;
        Serial.println("Fin de rutina");
   } 
}
