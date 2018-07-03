#include <LiquidCrystal.h>
const int rs = 12, en = 8, d4 = 5, d5 = 4, d6 = 13, d7 = 2;
int temp=0;
int temp1=0;
float potchange=0;
int sensorPin=A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() 
{
  			  lcd.begin(16, 2);              
}
void loop()
{
  temp=analogRead(sensorPin);
  potchange=temp;
  temp1=15+(temp/1023.0)*41.0;    //Maps change in pot wiper between integers 15 to 56
  lcd.setCursor(0, 0);
  lcd.print("Set Temp: ");
  lcd.setCursor(10, 0);
  lcd.print(temp1);
}
