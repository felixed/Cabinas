/*  Keypadtest.pde
 *
 *  Demonstrate the simplest use of the  keypad library.
 *
 *  The first step is to connect your keypad to the
 *  Arduino  using the pin numbers listed below in
 *  rowPins[] and colPins[]. If you want to use different
 *  pins then  you  can  change  the  numbers below to
 *  match your setup.
 *
 */
#include <Keypad.h>
#include "Wire.h"

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'#','0','*','D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 5, 6, 7, 8 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 9, 10, 11, 12 }; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

#define ledpin 13

void setup()
{
  pinMode(ledpin,OUTPUT);
  digitalWrite(ledpin, HIGH);
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    switch(key){
      case '0':
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write('x');        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      
      case 'A': /* Red */
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write('7');        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      case 'B': /* Green */
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write('8');        // sends five bytes
        Wire.endTransmission();    // stop transmitting
      case 'C': /* Blue */
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write('9');        // sends five bytes
        Wire.endTransmission();    // stop transmitting
        
      default:
        Wire.beginTransmission(4); // transmit to device #4
        Wire.write(key);        // sends five bytes
        Wire.endTransmission();    // stop transmitting
    }
    Serial.println(key);
  }
}
