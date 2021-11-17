#include <Wire.h>
#include "MMA7660.h"
#include "rgb_lcd.h"

class Flipper 
{ 
  public:
  float currentState = 0;
  float lastState = 0;   
  float limit = 0.8;  
  int onFlip(int input)
  {
    lastState = currentState;
    if(input > limit) {
      currentState = 1;
    } 
    else if (input < -limit) 
    {
      currentState = -1;
    }
    else
    {
      currentState = 0;
    }
    if(lastState != currentState) 
    {
      currentState;
    }
    else
    {
      return 0;
    }
  }
};


float x, y, z;

MMA7660 accelmeter;
rgb_lcd lcd;
Flipper flipX;

void setup() {
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
}
