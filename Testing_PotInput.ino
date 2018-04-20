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

// PID Values for Cooling
int kp=20,kd=12,ki=1;

// PID Values for Heating 
//int kp=30,kd=580,ki=0.05;

////////////////////////////////////////////
// PID Values for Cooling
//int kp=20,kd=12,ki=1;

//kp=10,kd=500,ki=0; -- for 49 at 46
//kp=20,kd=550,ki=0; -- for 49 at 47-48
//kp=30,kd=580,ki=0; -- for 49 at 48-49-50
////////////////////////////////////////////

int temperature_read=0;
int set_temperature=0;

int PID_error=0;

float previous_error = 0;
float PID_p=0,PID_d=0,PID_i=0,PID_value=0;
float elapsedTime, Time, timePrev;

void setup() 
{
            Time = millis(); 
            // Timer Setup for High Frequency PWM
           pinMode(10,OUTPUT);
           pinMode(9,OUTPUT);
            pinMode(3, OUTPUT);
            //pinMode(11,OUTPUT);
            TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);  
            TCCR2B = _BV(CS20);
            //OCR2A = 127;
            OCR2B = 0;
            
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
  temp1=15+(temp/1023.0)*41.0;

  // LCD Printing
  
  lcd.print(temp1);
  lcd.setCursor(13, 0);
  lcd.print("C"); 
  lcd.setCursor(0,1);
  lcd.print("Actual Temp:");
  lcd.print((int)DHT.temperature);
  //lcd.print(cel);
  lcd.setCursor(15,1);
  lcd.print("C");

  
  
  //OCR2B = (potchange/1024)*255 ;
  
//  Serial.println(" LM 35 Temp  ");
//  Serial.println((int)(cel));
//  Serial.println(" Actual Temperature  ");
  Serial.println(DHT.temperature);  
//  Serial.println(" Set Temperature ");
  Serial.println(temp1);
  
  set_temperature=temp1;
  temperature_read= DHT.temperature;
  //temperature_read= cel;
  PID_error = (temperature_read - set_temperature) ;
//  Serial.println("PID Error");
//  Serial.println(PID_error);
  PID_p = kp * PID_error;
 
  PID_i = (PID_i + (ki * PID_error));
  
  timePrev = Time;                            
  Time = millis();                            
  elapsedTime = (Time - timePrev) / 1000; 
  PID_d = kd*((PID_error - previous_error)/elapsedTime);

  PID_value = PID_p + PID_d + PID_i ;

   if(PID_value < 0 || PID_error<0 )
    {    PID_value = 0;
        //|| PID_p < 0 || PID_error<0
//         Serial.println("Flag");  
    }
  if(PID_value > 255)  
    {    PID_value = 255;  }
  
  OCR2B=PID_value;
  previous_error = PID_error; 
  
//  Serial.println("PWM Value ");
//  Serial.println(PID_value);
//  Serial.println("PID P");
//  Serial.println(PID_p);
//  Serial.println("PID D");
//  Serial.println(PID_d);
//  Serial.println("PID I");
//  Serial.println(PID_i);
  delay(1500);
//  if (temp1>30){
//     digitalWrite(10,HIGH);
//  digitalWrite(9,LOW);
//  }
//  else{
//  digitalWrite(10,LOW);
//  digitalWrite(9,HIGH);
//  }
}

