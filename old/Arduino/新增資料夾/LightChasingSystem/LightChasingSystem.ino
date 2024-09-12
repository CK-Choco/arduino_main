/*
專題名稱:追光系統
A0:光敏模組E
A1:光敏模組W
A2:微動開關min
A3:微動開關max
A4:負載電壓
A5:附載電流

13:伺服馬達E
12:伺服馬達W
11:藍芽RXD
10:藍芽TXD
20:顯示SDA
21:顯示CSL
*/

//(函式庫)程式庫
#include <Wire.h>  //I2C
//#include <LiquidCrystal_I2C.h>  //LCD_I2C
#include <Servo.h>  //伺服馬達

//建立伺服馬達物件(SERVO)
Servo myservo_left;   //左邊伺服馬達
Servo myservo_right;  //右邊伺服馬達

//預設值
int sensorLeft = 0;                           //設A0為sensorLeft
int sensorRight = 1;                          //設A1為sensorRight
int val1, val2, val3, val4 = 135, val5 = 45;  //設val1,val2,val3為光敏變數
//初始程式
void setup() {
  myservo_left.attach(13);   //設myservo_left 為13pin
  myservo_right.attach(12);  //設myservo_right為12pin
}
//重複程式
void loop() {
  val1 = analogRead(sensorLeft);   //設sensorLeft為val1
  val2 = analogRead(sensorRight);  //設sensorLeft為val2
  do {
    val3 = val1 - val2;

    if (val3 > 20 && val3 < -20) {
      myservo_right.write(val4 - 10);
      myservo_left.write(val5 + 10);
    } else if (val3 < -20) {
      myservo_right.write(val5 + 10);
      myservo_left.write(val4 - 10);
    }
  } while (val3 >= 30 && val3 <= -30);
  delay(15);


}
