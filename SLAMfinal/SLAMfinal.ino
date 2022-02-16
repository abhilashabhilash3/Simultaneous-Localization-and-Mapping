int error = 0;          //Error generated by the different speeds of the motor
int sensorL = 0;        //IR proximity sensor on the Left ON by default
int sensorF = 0;        //IR proximity sensor on the Front ON by default
//int sensorR = 0;        //IR proximity sensor on the Right ON by default
int motorspeedr = 0;    //Motor speed of the Right motor
int motorspeedl = 0;    //Motor speed of the Left motor
long duration;          //Duration for which the Echo pin is HIGH
int distancefollow;
int durationfollow;
//int flag1 = 0;
//int flag = 0;
//int flag2 = 0;
int i = 0;
int readvalue = 0;      //To read the Initiation signal
int distance; 

void setup(){
  Serial.begin(9600);
  pinMode(9,OUTPUT);    //PWM for right motor
  pinMode(10,OUTPUT);   //PWM for left motor
  pinMode(4,OUTPUT);    //First motor control
  pinMode(5,OUTPUT);    //First motor control
  pinMode(6,OUTPUT);    //Second motor control
  pinMode(7,OUTPUT);    //Second motor control
  pinMode(11,OUTPUT);   //Trigger pin for SONAR sensor
  pinMode(12,INPUT);    //Echo pin for SONAR sensor
  pinMode(13,OUTPUT);   //To make the default LED glow
  pinMode(2,OUTPUT);    //To synchronise with the other Arduino board
  pinMode(3,OUTPUT);    //To synchronise with the other Arduino board
  pinMode(A4, OUTPUT);
  pinMode(A5, INPUT);
  //delay(10000);
}

void loop(){
  digitalWrite(13,HIGH);  //Makes default LED glow

  if( Serial.available( ) > 0)    //Check if there is any data available in the Serial port.
  {
    readvalue = Serial.read();    //Read data from serial port
  }

  if(readvalue == 'S')            //Initiation to start the process
  {
    sensorL = digitalRead(A2);    //Read Left IR sensor
    sensorF = digitalRead(A3);    //Read Front IR sensor
    //sensorR = digitalRead(A3);    //Read Right IR sensor

    //Serial.print(sensorL);
    //Serial.print("\t");
    //Serial.print(sensorF);
    //Serial.print("\t");
    //Serial.println(sensorR);
    delay(10);

    digitalWrite(2,LOW);  //Synchronise with the other Arduino Board
    delay(20);
    digitalWrite(2,HIGH);  //not required

    if(sensorL == HIGH && sensorF == LOW )  //Condition to move front
    {
      Serial.println("F");
      //distancefollow = SonarSensorfollow(); 
      MoveFront();
      for(i=0;i<60;i++)    //Servo motor should run here
      {
        Serial.println(SonarSensor());    //Print the distance returned from SonarSensor() subroutine
        delay(50);
      }      
    }
    else if(sensorL == LOW && sensorF == HIGH )    //Condition to move Right
    {
      Serial.println("L");
      //distancefollow = SonarSensorfollow(); 
      MoveLeft();
      for(i=0;i<60;i++)    //Servo motor should run here
      {
        Serial.println(SonarSensor());   //Print the distance returned from SonarSensor() subroutine
        delay(50);
      }
    }
    else if( sensorL == HIGH && sensorF == HIGH  )    //Condition to move front
    {
      Serial.println("R");
      MoveRight();
      //distancefollow = SonarSensorfollow(); 
      for(i=0;i<60;i++)
       {
       Serial.println(SonarSensor());
       delay(50);
       }        
    }
    else if(sensorL == LOW && sensorF == LOW)    //Condition to move left
    {
      Serial.println("L");
      //distancefollow = SonarSensorfollow(); 
      for(i=0;i<60;i++)
      {
        Serial.println(SonarSensor());
        delay(50);
      }
      MoveLeft();
    }
    readvalue = 99;    //Didn't understand this
  }
}

void MoveFront()
{
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

    //distancefollow = SonarSensorfollow();  
    error = lticks - rticks;
    //delay(15);
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
    
    distancefollow = SonarSensorfollow();
    
    if( distancefollow < 5)    //????
    {
      analogWrite(9,100);
      analogWrite(10,120);
      digitalWrite(4,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
    }
    else if(distancefollow > 5 && distancefollow < 6)  //change made
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
    if(digitalRead(A4)==HIGH)    //Check this condition
    {
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);
    }
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

void MoveLeft()
{
  int A = 0;
  int B = 0;
  int dA = 0;
  int dB = 0;
  int lticks = 0;
  int rticks = 0;
  int lA = 0;
  int lB = 0;

  while(lticks < 8 && rticks < 10)    //to be verified
  {
    A = (digitalRead(A0) == HIGH) ? 1 : 0;    //What is connected to analog pin A0?
    B = (digitalRead(A1) == HIGH) ? 1 : 0;    //What is connected to analog pin A1?
    dA = (A!=lA);
    dB = (B!=lB);
    
    lticks = (dA == 1) ? lticks += 1 : lticks;
    rticks = (dB == 1) ? rticks += 1 : rticks;
    lA = A;
    lB = B;
    
      analogWrite(9,150);
      analogWrite(10,150);
      digitalWrite(4,LOW );
      digitalWrite(5,HIGH);
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
  }
  
   while(lticks < 14)    //How these values are obtained?
  {
    A = (digitalRead(A0) == HIGH) ? 1 : 0;
    B = (digitalRead(A1) == HIGH) ? 1 : 0;

    //Serial.print(rticks);
    //Serial.print('\t');
    //Serial.println(lticks);
    delay(10);
    dA = (A!=lA);
    dB = (B!=lB);
    lticks = (dA == 1) ? lticks += 1 : lticks;
    rticks = (dB == 1) ? rticks += 1 : rticks;
    lA = A;
    lB = B;

    analogWrite(9,120);
    analogWrite(10,100);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
  }  
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
}

void MoveRight()
{
  int A = 0;
  int B = 0;
  int dA = 0;
  int dB = 0;
  int lticks = 0;
  int rticks = 0;
  int lA = 0;
  int lB = 0;

  while( rticks < 12 )    //Even here
  {
    A = (digitalRead(A0) == HIGH) ? 1 : 0;
    B = (digitalRead(A1) == HIGH) ? 1 : 0;

    //Serial.print(rticks);
    //Serial.print('\t');
    //Serial.println(lticks);
    delay(10);

    dA = (A!=lA);
    dB = (B!=lB);
    lticks = (dA == 1) ? lticks += 1 : lticks;
    rticks = (dB == 1) ? rticks += 1 : rticks;
    lA = A;
    lB = B;
    analogWrite(9,100);
    analogWrite(10,120);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
  }
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
}

int SonarSensor()
{
  digitalWrite(3,LOW);    //Not required
  delay(20);
  digitalWrite(3,HIGH);    //Not Required
  
  
  digitalWrite(11,LOW);
  delayMicroseconds(2);
  digitalWrite(11,HIGH);
  delayMicroseconds(10);
  digitalWrite(11,LOW);
  duration = pulseIn(12,HIGH);
  distance = (duration/2) / 29.1; 
  return distance;
}

int SonarSensorfollow()
{
  digitalWrite(A4,LOW);
  delayMicroseconds(2);
  digitalWrite(A4,HIGH);
  delayMicroseconds(10);
  digitalWrite(A4,LOW);
  durationfollow = pulseIn(A5,HIGH);
  distancefollow = (durationfollow/2) / 29.1; 
  return distancefollow;
}



