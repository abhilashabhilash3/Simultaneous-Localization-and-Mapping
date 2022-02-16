void setup() {
  // put your setup code here, to run once:
    pinMode(9,OUTPUT);    //PWM for right motor
      pinMode(4,OUTPUT);    //First motor control
  pinMode(5,OUTPUT);    //First motor control
  digitalWrite(9, HIGH);

}

void loop()
{
  // put your main code here, to run repeatedly:
  int A = digitalRead(A0);
  Serial.print(A);
  Serial.print("\n");
  digitalWrite(4,LOW);  //Code to move forward
  digitalWrite(5,HIGH);
}
