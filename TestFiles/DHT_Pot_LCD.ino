#include <dht.h>
#include <LiquidCrystal.h>
dht DHT;
#define DHT11_PIN 7

const int rs = 12, en = 8, d4 = 5, d5 = 4, d6 = 13, d7 = 2;
int temp=0;
int temp1=0;
float potchange=0;
int sensorPin=A0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() 
{
  			  lcd.begin(16, 2);
          Serial.begin(9600);     
}
void loop()
{

  // Reading Potentiometer
  temp=analogRead(sensorPin);
  potchange=temp;
  temp1=15+(temp/1023.0)*41.0;
  
  // For Reading DHT11
  int chk = DHT.read11(DHT11_PIN);
  
  // Printing on LCD
  lcd.setCursor(0, 0);
  lcd.print("Set Temp: ");
  lcd.setCursor(10, 0);
  lcd.print(temp1);
  lcd.setCursor(13, 0);
  lcd.print("C"); 
  lcd.setCursor(0,1);
  lcd.print("Actual Temp:");
  lcd.print((int)DHT.temperature);
  lcd.setCursor(15,1);
  lcd.print("C");
 
 // Printing on Serial Monitor
  Serial.print("Set Temperature = ");
  Serial.println(temp1);
  Serial.print("Current Temperature = ");
  Serial.println(DHT.temperature);
  
  delay(2000);
}
