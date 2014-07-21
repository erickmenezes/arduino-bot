#include <Servo.h> 
 
#define LEFT_PIN 10
#define RIGHT_PIN 12

Servo left;
Servo right;
 
void setup() 
{ 
  //left.attach(LEFT_PIN);
  right.attach(RIGHT_PIN);
} 
 
void loop() 
{ 
  //knee(left, 45, 0);
  knee(right, 45, 0);
} 

void knee(Servo knee, int initPos, int endPos)
{
  delay(1000);
  knee.write(initPos);
  delay(1000); 
  knee.write(endPos);    
}
