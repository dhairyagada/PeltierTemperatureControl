#include <dht.h>
dht DHT;
#define DHT11_PIN 7

int RoomTemp=0;

void setup()
{
    Serial.begin(9600);
}
void loop()
{
    Serial.println((int)DHT.temperature); 
    delay(1200);
}
