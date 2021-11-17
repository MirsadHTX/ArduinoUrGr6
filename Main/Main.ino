#include <Wire.h>
#include "MMA7660.h"
#include "rgb_lcd.h"
float x, y, z;

MMA7660 accelmeter;
rgb_lcd lcd;
Flipper flipX;

void setup() {
  int state = 0;
  const maxState = 4;
  
	lcd.begin(16, 2);
	accelmeter.init(); 
   }

void loop() {
  accelmeter.getAcceleration(&x, &y, &z); // Tager memory address som input
	lcd.clear();
	lcd.print(x);
	lcd.print(" ");
	lcd.print(y);
	lcd.print(" ");
	lcd.print(z);

  if(flipX.onFlip(x)!=0)
  {
    digitalWrite(4,HIGH);
  } else {
    digitalWrite(4, LOW);
  }
  delay(50);

  if(OnFlip()==1)
  {
    if(state == maxState) {
      state = 0;
    } else {
      state += 1    
    }
  }

  switch(state)
  {
    case 1:

      break;
    case 2:

      break;
    case 3:

      break;
    case maxState:

      break;
    default:
}
