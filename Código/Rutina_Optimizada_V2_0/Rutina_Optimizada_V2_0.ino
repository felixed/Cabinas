#include <SoftwareSerial.h>
#include <Wtv020sd16p.h> //Librería del MP3
#include <Wire.h>

SoftwareSerial mySerial(14, 15); // RX, TX
bool I2C = false;

/* SECUENCIA 1 */
int const seq1[20]={0x081,    //hex 81, dec 129
                    0x809,   //hex 809, dec 2057
                    0x300,   //hex 300, dec 768
                    0x211,   //hex 211, dec 529
                    0x041,    //hex 41, dec 65
                    0x460,   //hex 460, dec 1120
                    0x448,   //hex 448, dec 1096
                    0x00E,     //hex E, dec 14
                    0x081,    //hex 81, dec 129
                    0x288,   //hex 288, dec 648
                    0x081,    //hex 81, dec 129
                    0x809,   //hex 809, dec 2057
                    0x300,   //hex 300, dec 768
                    0x211,   //hex 211, dec 529
                    0x041,    //hex 41, dec 65
                    0x460,   //hex 460, dec 1120
                    0x448,   //hex 448, dec 1096
                    0x00E,     //hex E, dec 14
                    0x244,   //hex 244, dec 580
                    0x00C};     //hex C, dec 12

/* SECUENCIA 2 */                    
int const seq2[20]={0x282,   //hex 282, dec 642
                    0x80A,   //hex 80A, dec 2058
                    0x502,   //hex 502, dec 1282
                    0x411,   //hex 411, dec 1041
                    0x281,   //hex 281, dec 641
                    0x4A0,   //hex 4A0, dec 1184
                    0x448,   //hex 448, dec 1096
                    0xE,     //hex E, dec 14
                    0x911,   //hex 911, dec 2321
                    0x308,   //hex 308, dec 776
                    0x82,    //hex 82, dec 130
                    0x80A,   //hex 80A, dec 2058
                    0x500,   //hex 500, dec 1280
                    0x411,   //hex 411, dec 1041
                    0x81,    //hex 81, dec 129
                    0x4A0,   //hex 4A0, dec 1184
                    0x448,   //hex 448, dec 1096
                    0xE,     //hex E, dec 14
                    0x244,   //hex 244, dec 580
                    0xC};     //hex C, dec 12

/* SECUENCIA 3 */
int const seq3[20]={0x284,   //hex 284, dec 644
                    0x80C,   //hex 80C, dec 2060
                    0x902,   //hex 902, dec 2306
                    0x811,   //hex 811, dec 2065
                    0x301,   //hex 301, dec 769
                    0x520,   //hex 520, dec 1312
                    0x44C,   //hex 44C, dec 1100
                    0xA,     //hex A, dec 10
                    0x891,   //hex 891, dec 2193
                    0x288,   //hex 288, dec 648
                    0x84,    //hex 84, dec 132
                    0x80C,   //hex 80C, dec 2060
                    0x900,   //hex 900, dec 2304
                    0x811,   //hex 811, dec 2065
                    0x101,   //hex 101, dec 257
                    0x520,   //hex 520, dec 1312
                    0x448,   //hex 448, dec 1096
                    0xE,     //hex E, dec 14
                    0x244,   //hex 244, dec 580
                    0xC};     //hex C, dec 12                   
int n;               // Variable auxiliar para determinar pin de salida del Arduino
int rutina;          // Número de rutina
int secuencia[20];   // Matriz de transferencia/copia de secuencias
int leerparo;        // Variable auxiliar para disparar paro
int paro;            // Variable que identifica si se precionó la tecla/botón paro
int resetPin = 20;   // The pin number of the reset pin.
int clockPin = 21;   // The pin number of the clock pin.
int dataPin = 17;    // The pin number of the data pin.
int busyPin = 16;    // The pin number of the busy pin

Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin); //Se declara el modulo MP3

/* Función para apagar todos los LEDs y el MP3 */
void apagar(){

  for(int i=2; i < 14; i++){
    digitalWrite(i,LOW);    
  }
  wtv020sd16p.stopVoice(); //Para detener reproducción de MP3 // Comentario temporal
}
                    
void leerbit(){

     for(int i=0; i < 20; i=i+2){
       if(paro){
        break;
      }
      mySerial.print(secuencia[i]);
      mySerial.print("/");
      mySerial.print(secuencia[i+1]);
      mySerial.println();
      for(int j=0; j < 15; j++){
        n=2;
        if(paro){
           break;
        }
        for(int k = 11; k >= 0; k--){
          if(!I2C)
            leerparo = mySerial.read();    
          if(leerparo == 'x'){
                paro=1;
                wtv020sd16p.stopVoice(); // Comentario temporal
                break;
              }
          if(bitRead(secuencia[i], k)){
              digitalWrite(n,HIGH);
              mySerial.print("1");
          }
          else{
              digitalWrite(n,LOW);
              mySerial.print("0");
          }
              n++;
        }
        mySerial.println();
        delay(1000);
        n=2;
        for(int m = 11; m >= 0; m--){
              if(!I2C)
                leerparo = mySerial.read();
              if(leerparo == 'x'){
                paro=1;
                wtv020sd16p.stopVoice(); // Comentario temporal
                break;
              }
              if(bitRead(secuencia[i+1], m)){
                digitalWrite(n,HIGH);
                mySerial.print("1");
              }else{
                digitalWrite(n,LOW);
                mySerial.print("0");
              }
              n++;
        }
        mySerial.println();
        delay(1000);
      }  
        mySerial.println();
    }
    apagar();

}

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
      rutina = mySerial.read();
    else
      Serial.println("I2C");
    I2C = false;  
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
