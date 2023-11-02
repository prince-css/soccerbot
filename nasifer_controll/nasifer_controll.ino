#include <hid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include "hidjoystickrptparser.h"
#include <Servo.h> 
USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);


Servo fkick;
Servo bkick;
int INA=7,INB=6,INC=A0,IND=A1,frkick=3,bckick=4,degree=60;
int pwm1=3,pwm2=5;
int speed1,speed2,oldspeed1,oldspeed2;
int x1,x2,y1,y2,hat,button; 


void setup() {
        pinMode(A1,OUTPUT);
        pinMode(5,OUTPUT);
        pinMode(4,OUTPUT);
        pinMode(6,OUTPUT);
        pinMode(7,OUTPUT);
        pinMode(3,OUTPUT);
        pinMode(9,OUTPUT);
        fkick.attach(frkick);
        bkick.attach(bckick);
        Serial.begin(9600);
        while (!Serial); 
        Serial.println("Start");
        
        if (Usb.Init() == -1)
                Serial.println("OSC did not start.");

        delay(200);

        if (!Hid.SetReportParser(0, &Joy))
                ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
}

void loop() {
          Usb.Task();
          jread();
          jprint();
          //gear();
          //bot_action();
        //backward(255,255);
}
void jread()
{
  x2 = JoyEvents.X_par;
  y2 = JoyEvents.Y_par;
  y1 = JoyEvents.Z_par;
  x1 = JoyEvents.Rz_par;
  hat = JoyEvents.hat_par;
  button = JoyEvents.but_par;
 // Serial.print(hat);
}
void jprint()
{
  Serial.print("Left :");
  Serial.print(x1);
  Serial.print("\t");
  Serial.print(y1);
  Serial.print("\t");
  Serial.print("Right :");
  Serial.print(x2);
  Serial.print("\t");
  Serial.print(y2);
  Serial.print("\t");
  Serial.print("Hat :");
  Serial.print(hat);
  Serial.print("\t");
  Serial.print("Button :");
  Serial.print(button);
  Serial.print("\t");
  Serial.println(" "); 
  delay(300);
}

void gear()
{

  if(hat==1 || hat==5)
  {
    speed1=60;           // G  E  A  R      O  N  E
    speed2=60;
    Serial.print(speed1);
  }
else if(hat==8 || hat==12)
  {
    speed1=150;         //  G  E  A  R      T  W  O
    speed2=150;
    Serial.print(speed1);
  }
else if(hat==2 || hat==6)
  {
    speed1=250;         // G  E  A  R      T  H  R  E  E
    speed2=250;
    Serial.print(speed1);
  }
 
  oldspeed1=speed1;
  oldspeed2=speed2;
}


void bot_action()
{
  if(y2==255)
  {
    if(hat!=4)
    {
    forward(speed1, speed2);
    Serial.print("  only forward  ");
    }
    else if(hat==4)
    {  
            kick();
           Serial.print("  kick  "); 
          

    forward( oldspeed1, oldspeed2);
    Serial.print("  +forward ");
    Serial.print(oldspeed1);
    }
  }
  
  else if(y2==0)
  {
    if(hat!=4)
    {
    backward(speed1, speed2);
    Serial.print("  only backward  ");
    }
    else if(hat==4)
    {
                kick();
                Serial.print("   kick  ");
              
    backward( oldspeed1, oldspeed2);
    Serial.print(" +backward  ");
    Serial.print(oldspeed1);
    }
  }
  
  else if(y2==128 || y2==127 )
  {
    if( hat!=4)
    {
        sstop();
        Serial.print(" only stop");
    }     
    else if(hat==4)
          {
            kick();
            Serial.print("stop+kick");
           // oldspeed1=oldspeed2=speed1=speed2=0; 
            }
  }
  else if(x2==255)
  {
    if(hat!=4)
    {
    power_right( speed1, speed2);
    Serial.print("only right turn");
    }
    else if(hat==4)
          {
            kick();
            Serial.print("right turn+kick");
            power_right( oldspeed1, oldspeed2);
          }
    
  }
  else if(x2==0)
  {
    if(hat!=4)
    {
    power_left( speed1, speed2);
    Serial.print("   only left turn   ");
    }
        else if(hat==4)
            {
              kick();
              Serial.print("left turn+kick");
              power_left( oldspeed1, oldspeed2);
            }
  }

//  else if(y1<100 && y2>100 && y2<150)
//  {
//    power_right(speed1,0);
//    Serial.print("upore right");
//  }
//    else if(y2<100 && y1>100 && y1<150)
//  {
//    power_left(0,speed2);
//    Serial.print("upore left");
//  }
//  else if(y1>150 && y2>100 && y2<150)
//  {
//    power_left(speed1,0);
//    Serial.print("niche left");
//  }
//  else if(y2>150 && y1>100 && y1<150)
//  {
//    power_right(0,speed2);
//    Serial.print("niche left");
//  }
//  
  
  
  Serial.println("");

  
}
void forward(int speed1,int speed2)
{
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);

  analogWrite(pwm1, speed1);
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);

  analogWrite(pwm2, speed2);
  Serial.println("f");
}
void backward(int speed1,int speed2)
{
 digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);

  analogWrite(pwm1, speed1);
  digitalWrite(INC, LOW);
  digitalWrite(IND, HIGH);

  analogWrite(pwm2, speed2);
  Serial.print("back");
}
void power_right(int speed1,int speed2)
{
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);

  analogWrite(pwm1, speed1);
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);

  analogWrite(pwm2, speed2);
  //Serial.print("pr");
}
void power_left(int speed1,int speed2)
{
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);

  analogWrite(pwm1, speed1);
  digitalWrite(INC, LOW);
  digitalWrite(IND, HIGH);

  analogWrite(pwm2, speed2);
  //Serial.print("pl");
}
void ektu_right(int speed1,int speed2)
{
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);

  analogWrite(pwm1,speed1);
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);

  analogWrite(pwm2, speed2);
  //Serial.print("er");
}
void ektu_left(int speed1,int speed2)
{
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);

  analogWrite(13, speed1);
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);

  analogWrite(8, speed2);
  //Serial.print("el");
}
void konakuni_front_left(int speed1,int speed2)
{
  digitalWrite(INA, HIGH);
  digitalWrite(INB, LOW);

  analogWrite(pwm1, speed1);
  digitalWrite(INC, LOW);
  digitalWrite(IND, HIGH);

  analogWrite(pwm2, speed2);
  //Serial.print("kl");
}
void konakuni_front_right(int speed1,int speed2)
{
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);

  analogWrite(pwm1, speed1);
  digitalWrite(INC, HIGH);
  digitalWrite(IND, LOW);

  analogWrite(pwm2, speed2);
  //Serial.print("kr");
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

void kick()
{
  digitalWrite(frkick,HIGH);
  digitalWrite(frkick,LOW);
  
}





