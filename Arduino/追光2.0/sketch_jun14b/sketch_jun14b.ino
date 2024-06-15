#include <Servo.h>  //伺服馬達
Servo myservo;
int z = 90, i, w;
void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  Serial.print("Start\n");
  //myservo.write(90);
}

void loop() {

  int x = analogRead(A0);
  int y = analogRead(A1);
  i = x - y;
  if (i > 20 || i > -20) {
    w = 1;
  }
  while (w = 1) {
    int x = analogRead(A0);
    int y = analogRead(A1);
    Serial.print(x);
    Serial.print("\n");
    Serial.print(y);
    Serial.print("\n");
    Serial.print(z);
    Serial.print("\n");
    Serial.print(i);
    Serial.print("\n");
    Serial.print(w);
    Serial.print("\n\n");

    delay(1000);
    if (i < 15 && i>-15) {
      w = w-1;
      break;
    } else {
      if (x < y) {
        z = z + 5.6;
        myservo.write(z);
        delay(15);
      } else if (x > y) {
        z = z - 5.6;
        myservo.write(z);
        delay(15);
      }
    }
    i = x - y;
  }
  Serial.print("NED\n");
}