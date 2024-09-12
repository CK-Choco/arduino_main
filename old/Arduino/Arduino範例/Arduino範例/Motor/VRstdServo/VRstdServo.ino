/* 可變電阻 + STD Servo                    © 華夏科大電子系 吳宗憲
 *  
*/
#include <Servo.h>

Servo myServo;             // 宣告伺服馬達程式物件
const byte potPin = A0;   // 宣告可變電阻的輸入端子
const byte servoPin = 9;  // 設定servoPin腳位
int val, pos;             // 暫存類比輸入值的變數

void setup() {  
  myServo.attach(servoPin);     // 設定伺服馬達的接腳
}

void loop() {
  val = analogRead(potPin);    // 讀取可變電阻的輸入值
  // 將類比輸入值 0~1024，對應成伺服馬達的 0~179 度
  // 請先查datasheet確認馬達可轉動角度
  pos = map(val, 0, 1023, 0, 179);
  myServo.write(pos); // 設定伺服馬達的旋轉角度
  delay(15); // 延遲一段時間，讓伺服馬達轉到定位
}
