// ************************************************      M      A        S       T     E       R       *******************************************************

#include<SoftwareSerial.h>
#include<Servo.h>
SoftwareSerial master(2, 3);
Servo motor;
char m;
int servo, value,degree;
char pcm;
void setup()
{
  pinMode(13, OUTPUT);
  motor.attach(9);
                                                                                                                                                                                                                                                                                                                                        Serial.begin(9600);
  Serial.println("master is on");
  master.begin(38400);
}
void loop()
{
  if (master.available() > 0)
  {
    m = master.read();

    value = m - '0';
    servo = value + 48;
    degree=map(servo,0,127,0,180);
    Serial.println(degree);

  }
  //  if(m=='1')
  //  {
  //    Serial.println("y");
  //    digitalWrite(10,HIGH);
  //
  //  }
  //  else if(m=='0')
  //  {
  //    digitalWrite(10,LOW);
  //
  //  }

  motor.write(degree);
  delay(10);

}

