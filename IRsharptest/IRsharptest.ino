int error = 0;          //Error generated by the different speeds of the motor
int sensorL = 0;        //IR proximity sensor on the Left ON by default
int sensorF = 0;        //IR proximity sensor on the Front ON by default
int sensorR = 0;        //IR proximity sensor on the Right ON by default
int motorspeedr = 0;    //Motor speed of the Right motor
int motorspeedl = 0;    //Motor speed of the Left motor
long duration;          //Duration for which the Echo pin is HIGH
int distancefollow;           //Distance to which an obstacle is present
//int flag1 = 0;
//int flag = 0;
//int flag2 = 0;
int i = 0;
int readvalue = 0;      //To read the Initiation signal

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(9,OUTPUT);    //PWM for right motor
  pinMode(10,OUTPUT);   //PWM for left motor
  pinMode(4,OUTPUT);    //First motor control
  pinMode(5,OUTPUT);    //First motor control
  pinMode(6,OUTPUT);    //Second motor control
  pinMode(7,OUTPUT);    //Second motor control
  pinMode(A4,OUTPUT);   //Trigger pin for SONAR sensor
  pinMode(A5,INPUT);    //Echo pin for SONAR sensor
//  pinMode(13,OUTPUT);   //Servo motor control
//  pinMode(2,OUTPUT);    //no use
//  pinMode(3,OUTPUT);    //no use
  //delay(10000);

}

void loop() 
{
  Serial.print(distancefollow);
  Serial.print("\n");
  int A = 0;
  int B = 0;
  int dA = 0;
  int dB = 0;
  int lticks = 0;
  int rticks = 0;
  int lA = 0;
  int lB = 0;
  int Sensor = 0;
  while(lticks < 26 && rticks < 26)    //Why 26?
  {
    A = (digitalRead(A0) == HIGH) ? 1 : 0;    //What is connected to analog pin A0?
    B = (digitalRead(A1) == HIGH) ? 1 : 0;    //What is connected to analog pin A1?
    dA = (A!=lA);
    dB = (B!=lB);

    lticks = (dA == 1) ? lticks += 1 : lticks;
    rticks = (dB == 1) ? rticks += 1 : rticks;
    lA = A;
    lB = B;
       //What is connected to analog pin A5?

    error = lticks - rticks;
    delay(1000);
    //Serial.print(rticks);
    //Serial.print('\t');
    //Serial.print(lticks);
    //Serial.print('\t');
    //Serial.println(error);

    if(error > 0)    //Controlling the speed of the motor
    {
      motorspeedr = 150 + (error * 10) ;     //If left motor is faster than right, increase the speed of right
      motorspeedl = 150 - (error * 10) ;
      analogWrite(9,motorspeedr);
      analogWrite(10,motorspeedl);
      digitalWrite(4,LOW);  //Code to move forward
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
    }
    else if (error < 0)
    {
      motorspeedr = 150 + error * 10 ;    //If right motor is faster than left, increase the speed of left
      motorspeedl = 150 - error * 10 ;
      analogWrite(9,motorspeedr);
      analogWrite(10,motorspeedl);
      digitalWrite(4,LOW);  //Code to move forward
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
    }
    else
    {
      motorspeedr = 150;    //If Both motors are running at equal speeds, then give equal values to both
      motorspeedl = 150;
      analogWrite(9,motorspeedr);
      analogWrite(10,motorspeedl);
      digitalWrite(4,LOW);  //Code to move forward
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
    }

     if( distancefollow < 5)    //????
    {
      analogWrite(9,100);
      analogWrite(10,120);
      digitalWrite(4,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
    }
    else if(distancefollow > 5 && distancefollow < 6)
    {
      analogWrite(9,150);
      analogWrite(10,150);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
    }
    else if(distancefollow > 6)
    {
      analogWrite(9,120);
      analogWrite(10,100);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
    }
  lticks = 0;
  rticks = 0;
  digitalWrite(9,HIGH);     //Check this condition
  digitalWrite(10,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  }
}

int SonarSensorfollow()
{
  digitalWrite(A4,LOW);
  delayMicroseconds(2);
  digitalWrite(A4,HIGH);
  delayMicroseconds(10);
  digitalWrite(A4,LOW);
  int durationfollow = pulseIn(A5,HIGH);
  distancefollow = (durationfollow/2) / 29.1; 
  return distancefollow;
}

