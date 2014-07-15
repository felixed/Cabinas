#include "Seq.h"

extern Wtv020sd16p wtv020sd16p;
extern int paro;
extern SoftwareSerial mySerial;
extern int secuencia[];
extern int n;
extern bool I2C;
extern int leerparo;
extern ShiftReg shiftReg;

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
              shiftReg.digitalWriteMS(1,n,HIGH);
              mySerial.print("1");
          }
          else{
              shiftReg.digitalWriteMS(1,n,LOW);
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
                shiftReg.digitalWriteMS(1,n,HIGH);
                mySerial.print("1");
              }else{
                shiftReg.digitalWriteMS(1,n,LOW);
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
