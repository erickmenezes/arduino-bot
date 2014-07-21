#include <Servo.h> 

#define KNEE_RIGHT_PIN 2
#define HIP_RIGHT_PIN 3
#define HIP_LEFT_PIN 4
#define KNEE_LEFT_PIN 5

#define WALK_DELAY 1000 //microseconds
#define LEG_DELAY 500 //microseconds

Servo kneeLeft;
Servo hipLeft;
Servo kneeRight;
Servo hipRight; 

void setup() 
{ 
  hipLeft.attach(HIP_LEFT_PIN);
  kneeLeft.attach(KNEE_LEFT_PIN);
  hipRight.attach(HIP_RIGHT_PIN);  
  kneeRight.attach(KNEE_RIGHT_PIN);
} 
 
void loop() 
{ 
  leftLeg();
  delay(WALK_DELAY);
  rightLeg();
  delay(WALK_DELAY);
} 

// Todos os servos começam em 90º
void rightLeg()
{
  hipRight.write(135); //end    
  delay(LEG_DELAY);
  kneeRight.write(180); //init (kneeInitPos + 90)
  delay(LEG_DELAY - 200); 
  hipRight.write(90); //init
  kneeRight.write(90); //init
}

void leftLeg()
{
  hipLeft.write(45); //end    
  delay(LEG_DELAY);
  kneeLeft.write(0); //init (kneeInitPos - 90)
  delay(LEG_DELAY - 200); 
  hipLeft.write(90); //init
  kneeLeft.write(90); //init
}

