void setup() 
{
  // put your setup code here, to run once:
pinMode(2,OUTPUT);
Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(2,HIGH);
  delay(3000);
  digitalWrite(2,LOW);
  delay(1000);

}
