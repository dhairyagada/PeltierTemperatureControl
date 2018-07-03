#include <LiquidCrystal.h>
const int rs = 12, en = 8, d4 = 5, d5 = 4, d6 = 13, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() 
{
  			  lcd.begin(16, 2);
              lcd.setCursor(2, 0);
              lcd.print("Hello World");
  			  delay(1000);
}
void loop()
{
  lcd.setCursor(2,1);
  lcd.print("Hello World");
}
