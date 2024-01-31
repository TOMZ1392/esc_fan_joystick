/*
 Joystick ESC fan control
*/

#include <Servo.h>
#define THROTT_LIM  170
#define ESC_PIN  9

Servo ESC;  

   
void setup() {
  Serial.begin(9600);
   
  pinMode(A1,INPUT);
  pinMode(ESC_PIN,OUTPUT);
  ESC.attach(ESC_PIN,1000,2000); 

  ESC.write(0);
  delay(5000);
}



void driveESC(int val)
{
  static int thrott=0;
  if(val < -2 || val > 2)
  { 
    if(val < -2 && thrott > 5)
    {
      thrott-=5;
      }
      else if(val >2 && thrott < THROTT_LIM)
      {
        thrott+=1;
        }
    Serial.println(thrott);
    if(thrott< THROTT_LIM){    
        ESC.write(thrott);
    }
  } 
}

void loop() {
  int val;
  val = analogRead(A1);           
  val = map(val, 0, 1023, -10, 10); 
  Serial.println(val);   
  driveESC(val);                 
  delay(200);                           
}