/*
 * Std Servo 範例        © 華夏科大電子系 吳宗憲
 * 工作電壓：DC5V
 * 
 * 使用 Servo.h 函式庫時，因為需使用PWM，所以會影響原本的PWM腳位。
 * 不管有無接伺服馬達，數位腳位9與10便無法輸出PWM。
 * 所以當使用此函式庫時，我們通常會將伺服馬達的訊號線接在數位腳位9或10。
 * 本範例直接以脈衝寬度控制Servo
 * 要注意的是，必須查詢伺服馬達的規格表，查知正確的脈衝寬度範圍。
 * 使用writeMicroseconds時也要小心，不可傳入超出範圍的值，否則會損壞伺服馬達。
 */
#include <Servo.h> //伺服馬達的函式庫
#define servoPIN 9  //伺服馬達 連接D9

Servo myservo;

void setup() 
{ 
  myservo.attach(servoPIN, 500, 2400); // 修正脈衝寬度範圍
  myservo.write(90); // 一開始先置中90度
  delay(3000);
} 

void loop() 
{
  for(int i = 500; i <= 2400; i+=100){
    myservo.writeMicroseconds(i); // 直接以脈衝寬度控制
    delay(300);
  }
  for(int i = 2400; i >= 500; i-=100){
    myservo.writeMicroseconds(i);
    delay(300);
  }
}

