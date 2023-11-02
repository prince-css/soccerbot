#include <hid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include "hidjoystickrptparser.h"
//#include <Servo.h> 

//#define DEBUG true

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);


//Servo fkick;
//Servo bkick;
//int INA=A2,INB=A3,INC=A0,IND=A1,frkick=3,bckick=4,degree=60;
//int pwm1=6,pwm2=5;
int speed1=20,speed2=20,oldspeed1=20,oldspeed2=20;




int x1,x2,y1,y2,hat,button; 
//ulta kore dilam
int R_EN1=4,L_EN1=2,R_EN2=8,L_EN2=7,RPWM2=5,LPWM2=3,LPWM1=9,RPWM1=6;

void setup() {
        pinMode(R_EN1,OUTPUT);
        pinMode(L_EN1,OUTPUT);
        pinMode(RPWM1,OUTPUT);
        pinMode(LPWM1,OUTPUT);
        pinMode(R_EN2,OUTPUT);
        pinMode(L_EN2,OUTPUT);      
        pinMode(RPWM2,OUTPUT);
        pinMode(LPWM2,OUTPUT);
//        fkick.attach(frkick);
//        bkick.attach(bckick);
//        
//#ifdef DEBUG
        Serial.begin(9600);
        while (!Serial); 


        Serial.println("Start");
//#endif        
        if (Usb.Init() == -1){
//          #ifdef DEBUG   
                Serial.println("OSC did not start.");
        delay(200);
//        #endif
        }

        if (!Hid.SetReportParser(0, &Joy))

               ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
}

void loop() {
          Usb.Task();
          jread();

//         #ifdef DEBUG 
          //jprint();
//         #endif
         
          gear();
          bot_action();
        //forward(255,255);
}
void jread()
{
  x2 = JoyEvents.X_par;
  y2 = JoyEvents.Y_par;
  y1 = JoyEvents.Z_par;
  button = JoyEvents.Rz_par;
  hat = JoyEvents.hat_par;
  x1 = JoyEvents.but_par;
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
  if(y1<100 && y2<100)
  {
    
    forward(speed1, speed2);
    
    Serial.println("  only forward  ");
   
   
  }
  
  else if(y1>150 && y2>150)
  {
   
    backward(speed1, speed2);
   
    Serial.println("  only backward  ");
    
  }
  
  else if(y1>120 && y1<140 && y2>120 && y2<140 )
  {

        sstop();
        #ifdef DEBUG
        Serial.println(" only stop");
        #endif
   
  }
  else if(y1<100 && y2>150)
  {

    power_left( speed1, speed2);
    
    Serial.println("only right turn");
   
    
  }
  else if(y1>150 && y2<100)
  {
   
    power_right( speed1, speed2);
    
    Serial.println("   only left turn   ");
    
  }

  else if(y1<100 && y2>100 && y2<150)
  {
    forward(255,150);
    Serial.println("upore right");
  }
    else if(y2<100 && y1>100 && y1<150)
  {
    forward(150,255);
    Serial.println("upore left");
  }
  else if(y1>150 && y2>100 && y2<150)
  {
    backward(255,150);
   Serial.println("niche left");
  }
  else if(y2>150 && y1>100 && y1<150)
  {
    backward(150,255);
    Serial.println("niche left");
  }
  
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
void power_right(int speed1,int speed2)
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
void power_left(int speed1,int speed2)
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
void ektu_right(int speed1,int speed2)
{
  digitalWrite(R_EN1,HIGH);
  digitalWrite(L_EN1,HIGH);
  analogWrite(RPWM1,speed1);
  analogWrite(LPWM1,0);

  digitalWrite(R_EN2,HIGH);
  digitalWrite(L_EN2,HIGH);
  analogWrite(RPWM2,speed2);
  analogWrite(LPWM2,0);
  //Serial.print("er");
}
void ektu_left(int speed1,int speed2)
{
  digitalWrite(R_EN1,HIGH);
  digitalWrite(L_EN1,HIGH);
  analogWrite(RPWM1,speed1);
  analogWrite(LPWM1,0);

  digitalWrite(R_EN2,HIGH);
  digitalWrite(L_EN2,HIGH);
  analogWrite(RPWM2,speed2);
  analogWrite(LPWM2,0);
  //Serial.print("el");
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
//
void kick()
{
  
  
}
//
//
//
//

