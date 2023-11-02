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


//Servo fkick;
//Servo bkick;

int speed1=255,speed2=255,oldspeed1,oldspeed2;
int x1,x2,y1,y2,hat,button; 



int R_EN1=4,L_EN1=2,R_EN2=8,L_EN2=7,LPWM1=5,RPWM1=3,RPWM2=9,LPWM2=6;

void setup() {
        pinMode(R_EN1,OUTPUT);
        pinMode(L_EN1,OUTPUT);
        pinMode(RPWM1,OUTPUT);
        pinMode(LPWM1,OUTPUT);
        pinMode(R_EN2,OUTPUT);
        pinMode(L_EN2,OUTPUT);      
        pinMode(RPWM2,OUTPUT);
        pinMode(LPWM2,OUTPUT);
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
          //jprint();
          //gear();
          bot_action();
          //power_right(speed1,speed2);
        
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

    
  
  

  if(x2==2)
  {
    
    power_left( speed1, speed2);
    Serial.print("only right turn");
    
    
  }
  else if(x2==8)
  {
    
    power_right( speed1, speed2);
    Serial.print("   only left turn   ");
  
  }
    else if(x1==0)
  {
    
    forward(speed1, speed2);
    Serial.print("  only forward  ");
   
  }
  
  else if(x1==255)
  {
   
    backward(speed1, speed2);
    Serial.print("  only backward  ");
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
  else if(x2==64)
  {
    ektu_right(speed1, speed2);
    Serial.println("ek_left");
  }
  else if(x2==128)
  {
    ektu_left(speed1, speed2);
    Serial.println("ek_right");
  }
  else if(x2==16)
  {
    soft_right(speed1/2, speed2/2);
    Serial.println("so_left");
  }
  else if(x2==32)
  {
    ektu_left(speed1/2, speed2/2 );
    Serial.println("so_right");
  }
  
  
  else if(x1==128 || x1==127 )
  {
    
        sstop();
        Serial.print(" only stop");
    
  }
  Serial.println("");

  
}
void forward(int speed1,int speed2)
{
  digitalWrite(R_EN1,HIGH);
  digitalWrite(L_EN1,HIGH);
  analogWrite(RPWM1,speed1);
  analogWrite(LPWM1,0);

  digitalWrite(R_EN2,HIGH);
  digitalWrite(L_EN2,HIGH);
  analogWrite(RPWM2,speed2);
  analogWrite(LPWM2,0);
  Serial.println("f");
}
void backward(int speed1,int speed2)
{
  digitalWrite(R_EN1,HIGH);
  digitalWrite(L_EN1,HIGH);
  analogWrite(RPWM1,0);
  analogWrite(LPWM1,speed1);

  digitalWrite(R_EN2,HIGH);
  digitalWrite(L_EN2,HIGH);
  analogWrite(RPWM2,0);
  analogWrite(LPWM2,speed2);
  Serial.print("back");
}
void power_left(int speed1,int speed2)
{
  digitalWrite(R_EN1,HIGH);
  digitalWrite(L_EN1,HIGH);
  analogWrite(RPWM1,speed1);
  analogWrite(LPWM1,0);

  digitalWrite(R_EN2,HIGH);
  digitalWrite(L_EN2,HIGH);
  analogWrite(RPWM2,0);
  analogWrite(LPWM2,speed2);

//  analogWrite(pwm2, speed2);
  //Serial.print("pr");
}
void power_right(int speed1,int speed2)
{
  digitalWrite(R_EN1,HIGH);
  digitalWrite(L_EN1,HIGH);
  analogWrite(RPWM1,0);
  analogWrite(LPWM1,speed1);

  digitalWrite(R_EN2,HIGH);
  digitalWrite(L_EN2,HIGH);
  analogWrite(RPWM2,speed2);
  analogWrite(LPWM2,0);
  //Serial.print("pl");
}
void ektu_left(int speed1,int speed2)
{
  digitalWrite(R_EN1,HIGH);
  digitalWrite(L_EN1,HIGH);
  analogWrite(RPWM1,speed1);
  analogWrite(LPWM1,0);

  digitalWrite(R_EN2,HIGH);
  digitalWrite(L_EN2,HIGH);
  analogWrite(RPWM2,0);
  analogWrite(LPWM2,0);
  //Serial.print("er");
}
void ektu_right(int speed1,int speed2)
{
  digitalWrite(R_EN1,HIGH);
  digitalWrite(L_EN1,HIGH);
  analogWrite(RPWM1,0);
  analogWrite(LPWM1,0);

  digitalWrite(R_EN2,HIGH);
  digitalWrite(L_EN2,HIGH);
  analogWrite(RPWM2,speed2);
  analogWrite(LPWM2,0);
  //Serial.print("el");
}
void soft_left(int speed1,int speed2)
{
  digitalWrite(R_EN1,HIGH);
  digitalWrite(L_EN1,HIGH);
  analogWrite(RPWM1,speed1);
  analogWrite(LPWM1,0);

  digitalWrite(R_EN2,HIGH);
  digitalWrite(L_EN2,HIGH);
  analogWrite(RPWM2,0);
  analogWrite(LPWM2,speed2);

//  analogWrite(pwm2, speed2);
  //Serial.print("pr");
}
void soft_right(int speed1,int speed2)
{
  digitalWrite(R_EN1,HIGH);
  digitalWrite(L_EN1,HIGH);
  analogWrite(RPWM1,0);
  analogWrite(LPWM1,speed1);

  digitalWrite(R_EN2,HIGH);
  digitalWrite(L_EN2,HIGH);
  analogWrite(RPWM2,speed2);
  analogWrite(LPWM2,0);
  //Serial.print("pl");
}

void sstop()
{
  digitalWrite(R_EN1,HIGH);
  digitalWrite(L_EN1,HIGH);
  analogWrite(RPWM1,0);
  analogWrite(LPWM1,0);

  digitalWrite(R_EN2,HIGH);
  digitalWrite(L_EN2,HIGH);
  analogWrite(RPWM2,0);
  analogWrite(LPWM2,0);
 // Serial.println("stop");
}

