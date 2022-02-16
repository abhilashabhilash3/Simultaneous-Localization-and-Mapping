int error = 0;          //Error generated by the different speeds of the motor
int sensorL = 0;        //IR proximity sensor on the Left ON by default
int sensorF = 0;        //IR proximity sensor on the Front ON by default
//int sensorR = 0;        //IR proximity sensor on the Right ON by default
int motorspeedr = 0;    //Motor speed of the Right motor
int motorspeedl = 0;    //Motor speed of the Left motor

void setup()
{
  Serial.begin(9600);
  pinMode(9,OUTPUT);    //PWM for right motor
  pinMode(10,OUTPUT);   //PWM for left motor
  pinMode(4,OUTPUT);    //First motor control
  pinMode(5,OUTPUT);    //First motor control
  pinMode(6,OUTPUT);    //Second motor control
  pinMode(7,OUTPUT);    //Second motor control
}
void loop()
{
    sensorL = digitalRead(A2);    //Read Left IR sensor
    sensorF = digitalRead(A3);    //Read Front IR sensor
//    sensorR = digitalRead(A3);    //Read Right IR sensor
    delay(10);
    if(sensorL == LOW && sensorF == HIGH )  //Condition to move front
    {
      MoveFront();
    }
    else if( sensorL == HIGH && sensorF == LOW )    //Condition to move Left
    {
      MoveLeft();  
    }
    else if(sensorL == LOW && sensorF == LOW)    //Condition to move right
    {
      MoveRight();
    }
    else if( sensorL == HIGH && sensorF == HIGH )    //Condition to move Left
    {
      MoveRight();  
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
  while(lticks < 26 && rticks < 26)    //Why 26?
  {
    A = (digitalRead(A0) == HIGH) ? 1 : 0;    //What is connected to analog pin A0?
    B = (digitalRead(A1) == HIGH) ? 1 : 0;    //What is connected to analog pin A1?
    delay(10);
    dA = (A!=lA);
    dB = (B!=lB);
    lticks = (dA == 1) ? lticks += 1 : lticks;
    rticks = (dB == 1) ? rticks += 1 : rticks;
    lA = A;
    lB = B;
    error = lticks - rticks;
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

  while(lticks < 14)    //How these values are obtained?
  {
    A = (digitalRead(A0) == HIGH) ? 1 : 0;
    B = (digitalRead(A1) == HIGH) ? 1 : 0;
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
  lticks = 0;
  rticks = 0;
  digitalWrite(9,HIGH);     //Check this condition
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





