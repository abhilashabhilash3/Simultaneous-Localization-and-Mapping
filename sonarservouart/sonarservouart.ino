#include <Servo.h> 
Servo myservo;
int trigPin = 11;    //Trig - green Jumper
int echoPin = 12;    //Echo - yellow Jumper
long duration, cm;
 
void setup()
{
  //Serial Port begin
  Serial.begin(9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(9);
}
 
void loop()
{
  for(int pos = 0; pos <= 180; pos += 5)  // goes from 0 degrees to 180 degrees in steps of 5 degrees 
  { 
    myservo.write(pos);
    delay(25);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    cm = (duration/2) / 29.1;  
    Serial.print(cm);
    Serial.print("cm");
    Serial.println('\n');
    delay(50);
  }                       
  
  for(int pos = 180; pos>=0; pos-=5)     // goes from 180 degrees to 0 degrees in steps of 5 degrees 
  { 
    myservo.write(pos);
    delay(25);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    cm = (duration/2) / 29.1;  
    Serial.print(cm);
    Serial.print("cm");
    Serial.println('\n');
    delay(50); 
  }
} 
  


