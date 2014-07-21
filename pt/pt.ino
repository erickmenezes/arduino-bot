#include <pt.h>
#include <Servo.h> 
 
#define ECHO_PIN 3
#define TRIGGER_PIN 4
#define KNEE_PIN 10 //left
#define HIP_PIN 9 //left
//#define KNEE_PIN 12 //right
//#define HIP_PIN 13 //right

#define KNEE_INIT_ANGLE 45 //left
#define KNEE_END_ANGLE 0 //left
#define HIP_INIT_ANGLE 135 //left
#define HIP_END_ANGLE 180 //left
//#define KNEE_INIT_ANGLE 0 //right
//#define KNEE_END_ANGLE 45 //right
//#define HIP_INIT_ANGLE 0 //right
//#define HIP_END_ANGLE 45 //right


#define STOP_DISTANCE 50 //cm

static struct pt pt1, pt2;

Servo knee;
Servo hip;

long distance; //cm

void setup() 
{
  Serial.begin(9600);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  knee.attach(KNEE_PIN);
  hip.attach(HIP_PIN);
  
  PT_INIT(&pt1);
  PT_INIT(&pt2);
}

static int servoPT(struct pt *pt) 
{
  static unsigned long timestamp = 0;
  static unsigned long t1 = 0;
  static unsigned long t2 = 0;
  
  PT_BEGIN(pt);
  while(1) 
  {
    PT_WAIT_UNTIL(pt, millis() - timestamp > 500 );
    timestamp = millis();

    if (distance > STOP_DISTANCE)
    {
      PT_WAIT_UNTIL(pt, millis() - t1 > 1000);
      t1 = millis(); 
      knee.write(KNEE_INIT_ANGLE);
      t2 = millis();
      PT_WAIT_UNTIL(pt, millis() - t2 > 100);
      hip.write(HIP_INIT_ANGLE);
      
      PT_WAIT_UNTIL(pt, millis() - t1 > 1000);
      knee.write(KNEE_END_ANGLE);
      t2 = millis();
      PT_WAIT_UNTIL(pt, millis() - t2 > 100);
      hip.write(HIP_END_ANGLE);
      t1 = millis();
    }
  }
  PT_END(pt);
}

static int distancePT(struct pt *pt) 
{
  static unsigned long timestamp = 0;
  static unsigned long t1 = 0;
  
  PT_BEGIN(pt);
  while(1) 
  {
    PT_WAIT_UNTIL(pt, millis() - timestamp > 100);
    timestamp = millis();
    
    t1 = millis();
    distance = getDistance();
    
    Serial.print(distance);
    Serial.print("cm");
    Serial.println();
  }
  PT_END(pt);
}

void loop()
{
  servoPT(&pt1);
  distancePT(&pt2);
}

long getDistance()
{
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_PIN, LOW);
  
  return microsecondsToCentimeters(pulseIn(ECHO_PIN, HIGH));
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
