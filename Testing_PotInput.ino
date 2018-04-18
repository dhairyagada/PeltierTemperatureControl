#include <LiquidCrystal.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 7

// ------------------ N O T E   V E R Y    I M P -----------------------------------------------------------------
// THE CONNECTION OF PIN 13 of LCD is with PIN 13 of ARDUINO not PIN 3 as shown in Diagram reffered from website!!
// THE CONNECTION OF PIN 6 (Enable Pin) of LCD is with PIN 8 of ARDUINO not PIN 3 as shown in Diagram reffered from website!! 

const int rs = 12, en = 8, d4 = 5, d5 = 4, d6 = 13, d7 = 2;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int temp=0;
int temp1=0;
float potchange=0;
int sensorPin=A0;
int tempPin = A4;
int val=0;

void setup() 
{

            // Timer Setup for High Frequency PWM
           
            pinMode(3, OUTPUT);
            //pinMode(11,OUTPUT);
            TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);  
            TCCR2B = _BV(CS20);
            //OCR2A = 127;
            OCR2B = 127;
            
            Serial.begin(9600);

}

void loop() 
{ 
  // LCD Setup
  lcd.clear();
  lcd.begin(16, 2);
  lcd.print("Set Temp: ");
  lcd.setCursor(10, 0);
  
  // DHT11 Reading
  int chk = DHT.read11(DHT11_PIN);  
 
  // LM 35 Reading 
  val = analogRead(tempPin);
  float mv = ( val/1024.0)*5000; 
  float cel = mv/10;

  temp=analogRead(sensorPin);
  
  potchange=temp;
  temp1=-10+(temp/1023.0)*50.0;

  // LCD Printing
  
  lcd.print(temp1);
  lcd.setCursor(13, 0);
  lcd.print("C"); 
  lcd.setCursor(0,1);
  lcd.print("Actual Temp:");
  lcd.print((int)DHT.temperature);
  lcd.setCursor(15,1);
  lcd.print("C");
 
  OCR2B = (potchange/1024)*255 ;
  
  Serial.println(" LM 35 Temp  ");
  Serial.println((int)(cel));
  Serial.println(" DHT Temp  ");
  Serial.println(DHT.temperature);  
  delay(1500);
}

