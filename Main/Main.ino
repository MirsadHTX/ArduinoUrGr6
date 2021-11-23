#include <Wire.h>
#include "MMA7660.h"
#include "rgb_lcd.h"
#include "FlipperClass.h"
// #include "RandGen.h"

int state, flipCheck;
const int maxState = 4;

Flipper flipX;

MMA7660 accelmeter;
rgb_lcd lcd;

void setup() {
  state = 0;
    
  Serial.begin(9600);
  randomSeed(analogRead(0));

	lcd.begin(16, 8, 2);
  accelmeter.init(); 
}

void loop()
{ 
  float x, y, z;
  accelmeter.getAcceleration(&x, &y, &z); // Tager memory address som input
  delay(50);

  flipCheck = flipX.onFlip(x);
  
  switch(flipCheck)
  {
    case 1:
      if(state == maxState) 
      {
        state = 0;
      } 
      else 
      {
        state += 1;  
      }
      digitalWrite(2,HIGH);
      delay(100);
      digitalWrite(2,LOW);
      break;
      
    case -1:
      if(state == 0) 
      {
        state = maxState;
      } 
      else
      {
        state -= 1;  
      }
      digitalWrite(2,HIGH);
      delay(100);
      digitalWrite(2,LOW);
      break;
    
    default:
      break;
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
      getName();
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

void getName(void) {
  char names[30][10] = {
  "Anders",
  "Emil",
  "Fahmi",
  "Freja",
  "Gustav W.",
  "Gustav E.",
  "Haris",
  "Ismail",
  "Jabriil",
  "Jacob",
  "Ludvig",
  "Jeppe",
  "Jonatan",
  "Kasper",
  "Lovro",
  "Mathias",
  "Mie",
  "Mohammad",
  "Nelisa",
  "Nicolai",
  "Pernille",
  "Rasmus",
  "Robert",
  "Sarah",
  "Silas",
  "Simon",
  "Thoeger",
  "Tobias",
  "Taaha",
  "William"
  };
  lcd.print(names[random(0, 30)]);
  while (digitalRead(8) == 0) {
  }
}
