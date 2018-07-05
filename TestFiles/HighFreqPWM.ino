void setup() 
{
            pinMode(3, OUTPUT);
            
            TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20) | _BV(WGM21);  
            TCCR2B = _BV(CS20);
            
            OCR2B = 126;      // Change this between 0-255 to change duty cycle
}

void loop() 
{
  OCR2B = 126;      // Change this between 0-255 to change duty cycle
}
