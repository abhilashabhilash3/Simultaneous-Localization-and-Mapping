long duration;
int distance; 
//int flag1 = 0;
//int flag = 0;
//int flag2 = 0;
int i = 0;
int readvalue = 0;
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A4,OUTPUT);   //Trigger pin for SONAR sensor
  pinMode(A5,INPUT);    //Echo pin for SONAR sensor
  pinMode(13,OUTPUT);  
  pinMode(2,OUTPUT);    //no use
  pinMode(3,OUTPUT);    //no use

}

void loop() 
{
   digitalWrite(13,HIGH);  //not required
  // put your main code here, to run repeatedly:
   digitalWrite(2,LOW);  //not required
   delay(20);
   digitalWrite(2,HIGH);  //not required
   
   for(i=0;i<60;i++)    //Servo motor should run here
      {
        Serial.println(SonarSensor());    //Print the distance returned from SonarSensor() subroutine
        delay(50);
      }      

}

int SonarSensor()
{
  digitalWrite(3,LOW);  
  delay(20);
  digitalWrite(3,HIGH);    
  
  
  digitalWrite(A4,LOW);
  delayMicroseconds(2);
  digitalWrite(A4,HIGH);
  delayMicroseconds(10);
  digitalWrite(A4,LOW);
  duration = pulseIn(A5,HIGH);
  distance = (duration/2) / 29.1; 
  return distance;
}
