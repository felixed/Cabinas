#include "Seq.h"

extern Wtv020sd16p wtv020sd16p;
extern int paro;
extern SoftwareSerial mySerial;
extern int secuencia[];
extern int n;
extern bool I2C;
extern int leerparo;
extern ShiftReg shiftReg;
extern bool ROJO;
extern bool VERDE;
extern bool AZUL;

/* Función para apagar todos los LEDs y el MP3 */
void apagar() {
  for (int i = 0; i < 12; i++) {
    shiftReg.digitalWriteMS(1, i, LOW);
  }
  wtv020sd16p.stopVoice(); //Para detener reproducción de MP3 // Comentario temporal
  mySerial.flush();
  ROJO = false;
  VERDE = false;
  AZUL = false;
}

// Ejecuta la rutina
void leerbit() {

  for (int i = 0; i < 20; i = i + 2) {
    if (paro)
      break;
    mySerial.print(secuencia[i]);
    mySerial.print("/");
    mySerial.print(secuencia[i + 1]);
    mySerial.println();
    for (int j = 0; j < 15; j++) {
      
      n = 2;
      // Se detiene
      if (paro)
        break;
      // Enciende los LEDs correspondientes  
      for (int k = 11; k >= 0; k--) {
        // Checa si no se ha detenido
        if (mySerial.available() > 0 || Serial.available() || I2C){
          if(!I2C)
            leerparo = mySerial.read();
        }
        if (leerparo == 'x') {
          Serial.println("PARO");
          paro = 1;
          leerparo = 0;
          wtv020sd16p.stopVoice(); // Comentario temporal
          break;
        }
        // Enciende los LEDs
        if (bitRead(secuencia[i], k)) {
          shiftReg.digitalWriteMS(1, n, HIGH);
          mySerial.print("1");
        }
        else {
          shiftReg.digitalWriteMS(1, n, LOW);
          mySerial.print("0");
        }
        n++;
      }
      
      // Se espera 1 segundo
      mySerial.println();
      delay(1000);
      n = 2;
      
      // Enciende el resto de los LEDs
      for (int m = 11; m >= 0; m--) {
        // Checa si se detuvo
        if (mySerial.available() > 0 || Serial.available() || I2C){
          if(!I2C)
            leerparo = mySerial.read();
        }
        if (leerparo == 'x') {
          mySerial.println("PARO");
          leerparo = 0;
          paro = 1;
          wtv020sd16p.stopVoice(); // Comentario temporal
          break;
        }
        // Enciende los LEDs
        if (bitRead(secuencia[i + 1], m)) {
          shiftReg.digitalWriteMS(1, n, HIGH);
          mySerial.print("1");
        } else {
          shiftReg.digitalWriteMS(1, n, LOW);
          mySerial.print("0");
        }
        n++;
      }
      // Se espera 1 segundo
      mySerial.println();
      delay(1000);
    }
    mySerial.println();
  }
  apagar();

}
