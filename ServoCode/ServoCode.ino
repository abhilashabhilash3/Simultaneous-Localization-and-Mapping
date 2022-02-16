#include <Servo.h> 

Servo myservo;  
int pos = 0;    
int A = 0;
int dA = 0;
int lA = 0;
int B = 0;
int dB = 0;
int lB = 0;
int count = 0;
int count1 = 0;

void setup() 
{ 
  myservo.attach(9);
  myservo.write(0);
  Serial.begin(9600); 
} 

void loop() 
{ 
  A = (digitalRead(3) == LOW) ? 1 : 0;
  dA = (A!=lA);
  B = (digitalRead(2) == LOW) ? 1 : 0;
  dB = (B!=lB);
  count1 = (dB == 1) ? count1 +=1 : count1;
  count = (dA == 1) ? count +=1 : count;
  pos = (count == 2) ? pos += 3 : pos;
  pos = (count1 == 2) ? pos = 0 : pos;
  count = (count == 2) ? count = 0 : count;
  count1 = (count1 == 2) ? count1 = 0 : count1;
  pos = (pos >= 180) ? pos = 0 : pos;
  myservo.write(pos);
  lA = A;
  lB = B;
 // Serial.println(pos);
  delay(10);  
}
