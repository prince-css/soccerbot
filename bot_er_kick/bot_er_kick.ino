#include <Servo.h>
Servo myservo;  
void setup()
{
    myservo.attach(9);  
}

void loop() 
{
myservo.write(0);
delay(50);
myservo.write(70);
delay(350);
myservo.write(0);
delay(350);
}

