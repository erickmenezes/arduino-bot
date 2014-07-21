#include <Servo.h> 
 
#define ECHO_PIN 3
#define TRIGGER_PIN 4
#define SERVO_PIN 10

#define STOP_DISTANCE 50 //cm

Servo servo;

int pos = 0; //degree
long distance; //cm

void setup() 
{
  Serial.begin(9600);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servo.attach(SERVO_PIN);
}

void loop()
{
  distance = getDistance();
  
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  
  if (distance > STOP_DISTANCE)
  {
    servo.write(pos);
    delay(1000);
    servo.write(90);
    delay(1000);
  }
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
