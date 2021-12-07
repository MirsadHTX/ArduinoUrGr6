#include <Wire.h>
#include "MMA7660.h"
#include "rgb_lcd.h"
#include "FlipperClass.h"
// #include "RandGen.h"
#include <Wire.h>
#include "DS1307.h"

DS1307 clock;//define a object of DS1307 class

bool off = false;

int state, flipCheck, flipCheckY;
int score = 0;
const int maxState = 4;
const char names[30][10] = 
  {
  "Anders",
  "Emil",
  "Fahmi",
  "Freja",
  "Gustav W.",
  "Gustav E.",
  "Haris",
  "Ismail",
  "Jabril",
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


Flipper flip;

MMA7660 accelmeter;
rgb_lcd lcd;
long int unixTime = 1638446451;
float x_last, y_last, z_last = 0.0;

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
   // clock.setTime(unixTime);//write time to the RTC chip
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
      if(state >= maxState) 
      {
        state = 0;
      } 
      else 
      {
        state += 1;  
      }
      digitalWrite(4,HIGH);
      delay(100);
      digitalWrite(4,LOW);
      break;
      
    case -1:
      if(state <= 0) 
      {
        state = maxState;
      } 
      else
      {
        state -= 1;  
      }
      digitalWrite(4,HIGH);
      delay(100);
      digitalWrite(4,LOW);
      break;
    
    default:
      break;
  }
  x_last = x;
  y_last = y;
  z_last = z; 
  updateState(state, y, y_last);  
}

void updateState(int state, float y, float y_last)
 {
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
      lcd.print("State 4");
      break;
    case 3:
      //Serial.print((String)y_last + " " + (String)y);
      if(y_last < y - 0.3 || y_last > y + 0.3) { // for at forhindre skift hele tiden har vi en +- 0.3
        getName();
      }
      break;
    case maxState:
      game();
      break;
    default:
      break;
  }

 
}

void game()
{
  if(score == 0)
  {
    lcd.clear();
    lcd.print("Press the button");
  }
  if(digitalRead(2) == 1 && off == false)
  {
    score = score + 1;
    lcd.clear();
    lcd.print(score);
    off = true;
  }
  
  if(digitalRead(2) == 0)
  {
    off = false;
  }
  
  if(score >= 10)
  {
    lcd.clear();
    lcd.print("Time: ");
    lcd.print(score);
    delay(3000);
    score = 0;
  }
}

void getName() 
{
  lcd.clear();
  lcd.print(names[random(0, 30)]);
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

void stopUr()
{
    clock.getTime();
    lcd.print(clock.minute, DEC);
    lcd.print(":");
    lcd.print(clock.second, DEC);
    lcd.print("  ");
}
