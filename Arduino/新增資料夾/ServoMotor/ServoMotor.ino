#include <Servo.h>
Servo myservo1;
Servo myservo2;
int potpin1 = 0;
int potpin2 = 1;
int val, val2;
void setup() {
  myservo1.attach(3);
  myservo2.attach(4);
}

void loop() {




  val = analogRead(potpin1);
  val = map(val, 0, 1024, 0, 180);
  myservo1.write(180);
  val2 = analogRead(potpin2);
  val = map(val, 0, 1024, 180, 0);
  myservo2.write(0);
  delay(15);
}
