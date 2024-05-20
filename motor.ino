void motor(int left, int right)
{
  if(right>=0 && left>=0)
  {
     analogWrite(ENA, right);
     analogWrite(ENB,left);
     digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);
     digitalWrite(IN3,HIGH);
     digitalWrite(IN4,LOW);
    // Serial.println("both positive");
  }
  if(right<0&&left>0)
  {
   right=-right;
   // right=0;
     analogWrite(ENA, right);
     analogWrite(ENB,left);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
      digitalWrite(IN3,HIGH);
     digitalWrite(IN4,LOW);
  // Serial.println("left positive");
  }
  if(left<0&&right>=0)
  {
    left=-left;
    //left=0;
    analogWrite(ENA, right);
     analogWrite(ENB,left);
     digitalWrite(IN1,HIGH);
     digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
  // Serial.println("right positive");
  }
    if(right<0 && left<0)
  {
    left=-left;
    right=-right;
     analogWrite(ENA, right);
     analogWrite(ENB,left);
     digitalWrite(IN2,HIGH);
     digitalWrite(IN1,LOW);
     digitalWrite(IN4,HIGH);
     digitalWrite(IN3,LOW);
    // Serial.println("both negative");
  }
}
