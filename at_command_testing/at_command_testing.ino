#include<SoftwareSerial.h>
SoftwareSerial bt(34,35) ;//  RX=2  ;  TX=3
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
char a;
char c;
void setup() 
{
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
  Serial.begin(9600);
  Serial.println("I am ready");
  Serial.println("type your AT command");
  bt.begin(38400);
  
 
}

void loop() {
  if(Serial.available()>0)
  {
    a=Serial.read();
    bt.write(a);
  }
  if(bt.available()>0)
  {
    c=bt.read();
    Serial.write(c);
  }

}
