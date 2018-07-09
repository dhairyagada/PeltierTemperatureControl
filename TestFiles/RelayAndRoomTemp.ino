#include<dht.h>
#include<LiquidCrystal.h>
dht DHT;
#define DHT11_PIN 7

const int rs = 12, en = 8, d4 = 5, d5 = 4, d6 = 13, d7 = 2;
int temp=0;
int temp1=0;
float potchange=0;
int sensorPin=A0;
int RoomTemp=0;
int temperature_read=0;
int set_temperature=0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() 
{
           pinMode(10,OUTPUT);
           pinMode(9,OUTPUT);
           Serial.begin(9600);     

           // Recording Room Temperature in Initial Setup
           int chk = DHT.read11(DHT11_PIN);
           for(int i=0; i<=100; i++)
            {
              lcd.begin(16, 2);
              lcd.setCursor(2, 0);
              lcd.print("Initial Setup");
              lcd.setCursor(5, 1);
              lcd.print(i);
              RoomTemp=(int)DHT.temperature;
              lcd.setCursor(9, 1);
              lcd.print(RoomTemp);
   
              delay(100);
            }           
}
void loop()
{

      // Reading Potentiometer
      temp=analogRead(sensorPin);
      potchange=temp;
      temp1=15+(temp/1023.0)*41.0;
    
      set_temperature=temp1;
      temperature_read= DHT.temperature;
      
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

     // Relay Polarity
      
     if(set_temperature>=RoomTemp)
      {
            digitalWrite(9,HIGH);
            digitalWrite(10,HIGH);
      }
       else if(set_temperature<RoomTemp)
      {
            digitalWrite(9,LOW);
            digitalWrite(10,LOW);
      }
      
      delay(2000);
}
