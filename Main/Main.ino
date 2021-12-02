#include <Wire.h>
#include "MMA7660.h"
#include "rgb_lcd.h"
#include "FlipperClass.h"
// #include "RandGen.h"
#include <Wire.h>
#include "DS1307.h"

DS1307 clock;//define a object of DS1307 class


/*Function: Display time on the serial monitor*/




int state, flipCheck, flipCheckY;
const int maxState = 4;

Flipper flip;

MMA7660 accelmeter;
rgb_lcd lcd;
long int unixTime = 1638446451;


void setup() {
  state = 0;

   
  Serial.begin(9600);
  randomSeed(analogRead(0));

	lcd.begin(16, 8, 2);
  accelmeter.init(); 

  Serial.begin(9600);
    clock.begin();
 /*   clock.fillByYMD(2013, 1, 19); //Jan 19,2013
    clock.fillByHMS(12, 30, 50); //15:28 30"
    clock.fillDayOfWeek(SAT);//Saturday
   */ 
    clock.setTime(unixTime);//write time to the RTC chip
}

void loop()
{ 
  float x, y, z;
  accelmeter.getAcceleration(&x, &y, &z); // Tager memory address som input
  delay(50);

  flipCheck = flip.onFlip(x);
  flipCheckY = flip.onFlip(y);
  
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
    case 0:
      lcd.clear();
      printTime();
      break;
    case 1:
      lcd.clear();
      stopUr();
      break;    
    case 2:
      lcd.clear();
      getName(flipCheckY);
      lcd.print("State 3");
      break;
    case 3:
      lcd.clear();
      lcd.print("State 4");
      break;
    case maxState:
      lcd.clear();
      lcd.print("State 5");
      break;
    default:
      break;
  }

  
}

void getName(int yPos) 
{
  char names[30][10] = 
  {
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
    sleep_until(flip.onFlip(yPos));
}
void printTime() 
{
    clock.getTime();
    lcd.print(clock.hour, DEC);
    lcd.print(":");
    lcd.print(clock.minute, DEC);
    lcd.print(":");
    lcd.print(clock.second, DEC);
    lcd.print("  ");
    /* Serial.print(clock.month, DEC);
    Serial.print("/");
    Serial.print(clock.dayOfMonth, DEC);
    Serial.print("/");
    Serial.print(clock.year + 2000, DEC);
    Serial.print(" ");
    Serial.print(clock.dayOfMonth);
    Serial.print("*"); 
    
    switch (clock.dayOfWeek) { // Friendly printout the weekday
        case MON:
            Serial.print("MON");
            break;
        case TUE:
            Serial.print("TUE");
            break;
        case WED:
            Serial.print("WED");
            break;
        case THU:
            Serial.print("THU");
            break;
        case FRI:
            Serial.print("FRI");
            break;
        case SAT:
            Serial.print("SAT");
            break;
        case SUN:
            Serial.print("SUN");
            break;
    }
    lcd.println(" ");*/
}

void stopUr();
{
    clock.getTime();
    lcd.print(clock.minute, DEC);
    lcd.print(":");
    lcd.print(clock.second, DEC);
    lcd.print("  ");
}
