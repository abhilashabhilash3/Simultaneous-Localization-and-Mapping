 int joyPin1 = 0;                 // connecetd to analog pin 0
 int joyPin2 = 1;                 // connecetd to analog pin 1
 int value1 = 0;                  // variable to read the value from the analog pin 0
 int value2 = 0;                  // variable to read the value from the analog pin 1

 void setup() {
  Serial.begin(9600);
 }

 void loop() {
  // reads the value of the variable resistor 
  value1 = analogRead(joyPin1);   
  // this small pause is needed between reading
  // analog pins, otherwise we get the same value twice
  delay(100);             
  // reads the value of the variable resistor 
  value2 = analogRead(joyPin2);   
  Serial.print(value1);
  Serial.print('\t');
  Serial.println(value2);
  
  if((value1>=800)&&(value2>=500))
  {
    reverse();
  }
  
  if((value1>=0)&&(value2>=500))
  {
    forward();
  }
  
  if((value1>=500)&&(value2>=0))
  {
    turnright();
  }
  
  if((value1>=500)&&(value2>=800))
  {
    turnleft();
  }
