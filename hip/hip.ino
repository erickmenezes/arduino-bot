#include <Servo.h> 

#define LEFT_PIN 9
#define RIGHT_PIN 13

Servo left;
Servo right;

void setup() 
{ 
  left.attach(LEFT_PIN);
  //right.attach(RIGHT_PIN);
} 
 
void loop() 
{ 
  hip(left, 90, 45);
  //hip(right, 135, 90);
} 

void hip(Servo hip, int initPos, int endPos)
{
  delay(1000);
  hip.write(initPos);
  delay(1000); 
  hip.write(endPos);    
}

