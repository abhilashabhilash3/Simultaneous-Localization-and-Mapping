/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
int led = 13;

void setup() 
{                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

void loop() 
{
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
