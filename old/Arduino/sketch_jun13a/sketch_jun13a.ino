#include <Servo.h>  //含入伺服馬達程式庫 Servo.h
Servo myservo;      //命名伺服馬達為 myservo
int val, val1;
void setup() {
  Serial.begin(9600);
  myservo.attach(13);  //伺服馬達黃色線接 Arduino pin 13
}

void loop() {
  int potpinx = analogRead(A0);  //A0
  //int potpiny = analogRead(A1);  //A1
  //val1 = 1023-abs(potpinx - potpiny);
  //val = analogRead(potpinx) - analogRead(potpiny);    
  val=potpinx;       // x-y
  val = map(val, 1023, 0, 0, 180);  //轉換電位值 0-1023 至角度0-180 度, 因為伺服馬達的旋轉為 0-180 度
  myservo.write(val);                //轉動伺服馬達至角度 val
  Serial.println("potpinx:");
  Serial.println(potpinx);
  //Serial.println("potpiny:");
  //Serial.println(potpiny);
  Serial.println("x-y:");
  Serial.println(val1);
  Serial.println("val:");
  Serial.println(val);
  Serial.println("========================");
  delay(750);
}