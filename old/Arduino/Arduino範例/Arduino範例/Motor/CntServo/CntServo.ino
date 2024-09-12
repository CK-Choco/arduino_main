/* 連續型伺服馬達控制方向及轉速                    © 華夏科大電子系 吳宗憲
 * 本範例直接使用 Servo.h 函式庫
*/
#include <Servo.h>
Servo myServo;               // 宣告伺服馬達程式物件
const byte servoPin = 9;    // 設定servoPin腳位
int val;                    // 暫存類比輸入值的變數

void setup() {
  myServo.attach(servoPin); // 設定伺服馬達的接腳
}

void loop() {
  myServo.writeMicroseconds(1300); // CntServo 順時針旋轉
  delay(1000);  
  myServo.writeMicroseconds(1500); // CntServo 靜止
  delay(1000); 
  myServo.writeMicroseconds(1700); // CntServo 逆時針旋轉
  delay(1000); 
  myServo.writeMicroseconds(1500); // CntServo 靜止
  delay(1000);
}

