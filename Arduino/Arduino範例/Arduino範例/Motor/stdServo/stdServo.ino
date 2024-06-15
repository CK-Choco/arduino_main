/*
 * Std Servo 範例        © 華夏科大電子系 吳宗憲
 * 工作電壓：DC5V
 *  
 * 使用此 Servo.h 函式庫時，因為需使用PWM，所以會影響原本的PWM腳位。
 * 不管有無接伺服馬達，數位腳位9與10便無法輸出PWM。
 * 所以當使用此函式庫時，我們通常會將伺服馬達的訊號線接在數位腳位9或10。
 * 本範例直接以輸出角度控制Servo
 */
#include <Servo.h> //伺服馬達的函式庫
#define servoPIN 9  //伺服馬達 連接D9
Servo myservo;
int pos = 90;

void setup()
{
  myservo.attach(servoPIN);
  myservo.write(pos);
}

void loop()
{
/*  
  myservo.write(30);
  delay(2000);
  myservo.write(90);
  delay(2000);
  myservo.write(150);
  delay(5000);
*/  

  for(pos = 60;pos<=150;pos+=10){
    myservo.write(pos);
    delay(1000);
  }

  for(pos = 150;pos>=60;pos-=1){
    myservo.write(pos);
    delay(50);
  }

}

