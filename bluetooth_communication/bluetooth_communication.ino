#include<SoftwareSerial.h>
SoftwareSerial bt(2,3);
int INA=12,INB=11,INC=9,IND=10;
int pwm1=13,pwm2=8;
char rcv;
char val;
char mag;
void setup() 
{
  
 pinMode(13,OUTPUT);
 pinMode(12,OUTPUT);
 pinMode(11,OUTPUT);
 pinMode(10,OUTPUT);
 pinMode(9,OUTPUT);
 pinMode(8,OUTPUT);
 Serial.begin(9600);
 Serial.println("welcome");
 bt.begin(38400);
}

void loop() 
{
  
  if(bt.available()>0)
  {
    
    val=bt.read();
    
    Serial.println(val);
      if(val=='8')
      {
        Serial.println("forward");
        forward();
      }
      else if(val=='2')
      {
        Serial.println("backward");
        backward();
      }
      else if(val=='x')
      {
        Serial.println("power_left");
        power_left();
      }
      else if(val=='y')
      {
        Serial.println("power_right");
        power_right();
      }
      else if(val=='4')
      {
        Serial.println("ektu_left");
        ektu_left();
      }
      else if(val=='6')
      {
        Serial.println("ektu_right");
        ektu_right();
      }
      else if(val=='7' || val=='3')
      {
        Serial.println("konakuni_left");
        konakuni_front_left();
      }
      else if(val=='1' || val=='9')
      {
        Serial.println("konakuni_right");
        konakuni_front_right();
      }
      else
      {
        sstop();
        Serial.println("stop");
      }
  }
  else if(Serial.available()>0)
  {
    mag=Serial.read();
    bt.write(mag);
  }
}
void forward()
{
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);

  analogWrite(pwm1, 220);
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);

  analogWrite(pwm2, 220);
  //Serial.println("f");
}
void backward()
{
 digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);

  analogWrite(pwm1, 220);
  digitalWrite(INC, LOW);
  digitalWrite(IND, HIGH);

  analogWrite(pwm2, 220);
  //Serial.print("back");
}
void power_right()
{
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);

  analogWrite(pwm1, 170);
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);

  analogWrite(pwm2, 180);
  //Serial.print("pr");
}
void power_left()
{
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);

  analogWrite(pwm1, 180);
  digitalWrite(INC, LOW);
  digitalWrite(IND, HIGH);

  analogWrite(pwm2, 170);
  //Serial.print("pl");
}
void ektu_right()
{
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);

  analogWrite(13, 130);
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);

  analogWrite(8, 220);
  //Serial.print("er");
}
void ektu_left()
{
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);

  analogWrite(13, 220);
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);

  analogWrite(8, 130);
  //Serial.print("el");
}
void konakuni_front_left()
{
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);

  analogWrite(pwm1, 150);
  digitalWrite(INC, LOW);
  digitalWrite(IND, HIGH);

  analogWrite(pwm2, 140);
  //Serial.print("kl");
}
void konakuni_front_right()
{
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);

  analogWrite(pwm1, 140);
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);

  analogWrite(pwm2, 150);
 // Serial.print("kr");
}

void sstop()
{
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);

  analogWrite(pwm1, 0);
  digitalWrite(INC, LOW);
  digitalWrite(IND, LOW);

  analogWrite(pwm2, 0);
 // Serial.println("stop");
}

