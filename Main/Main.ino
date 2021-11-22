#include <Wire.h>
#include "MMA7660.h"
#include "rgb_lcd.h"
#include "FlipperClass.h"
// #include "RandGen.h"

int state;
const int maxState = 4;

Flipper flipX;

MMA7660 accelmeter;
rgb_lcd lcd;

void setup() {
  state = 0;

  // flipX = new Flipper();
  
  Serial.begin(9600);
  randomSeed(analogRead(0));

	lcd.begin(16, 2);
  accelmeter.init(); 
}

void loop()
{ 
  float x, y, z;
  accelmeter.getAcceleration(&x, &y, &z); // Tager memory address som input
  delay(50);
 
  if(flipX.onFlip(x)==1)
  {
    if(state == maxState) 
    {
      state = 0;
    } 
    else 
    {
      state += 1;  
    }
<<<<<<< HEAD
  }
=======
  } 
>>>>>>> 84e3b0426c5278b9172943517c32cf782cebf96b
  else if(flipX.onFlip(x)==-1)
  {
    if(state == 0) 
    {
      state = maxState;
      lcd.clear();
      lcd.cursor(2,1);
      lcd.print("Rolling over");
    } 
    else
    {
      lcd.print("Going back");
      lcd.cursor(0,1);
      state -= 1;  
    }
  }
    
switch(state)
  {
    case 1:
      /* char elev = classState();
      lcd.print(elev); */

      lcd.clear();
      lcd.print("State 1");
      break;    
    case 2:
      lcd.clear();
      lcd.print("State 2");
      break;
    case 3:
      lcd.clear();
      lcd.print("State 3");
      break;
    case maxState:
      lcd.clear();
      lcd.print("State 4");
      break;
    default:
      break;
  }
}
