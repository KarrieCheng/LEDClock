#include <Servo.h>

const int motor = 9;
const int led = 2;
Servo m1;

int speed = 0;

void setup()
{
  m1.attach(motor);
  m1.write(speed);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  m1.write(20);
  delay(1000);
  m1.write(37);
}

void loop()
{

}
