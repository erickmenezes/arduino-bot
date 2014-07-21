#define ECHO_PIN 3
#define TRIGGER_PIN 4

void setup() 
{
  Serial.begin(9600);
  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop()
{
  long cm;

  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_PIN, LOW);

  cm = microsecondsToCentimeters(pulseIn(ECHO_PIN, HIGH));
 
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
 
  delay(100);
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
