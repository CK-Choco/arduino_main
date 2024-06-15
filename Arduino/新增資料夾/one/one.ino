/*
OUT腳位
3為myservo
4為myservo1
10為藍芽 txd
11為藍芽 rxd
20為LCB sda
21為LCB scl
IN腳位
A0為光敏電阻X
A1為光敏電阻Y
A2為電壓PT
A3微電流AT
*/
// 程式庫
#include <Wire.h> // I2C函式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C函式庫
#include <Servo.h> // 伺服馬達函式庫

// BT
#include <SoftwareSerial.h>
const byte Txpin=11;
const byte Rxpin=10;
SoftwareSerial BT(Rxpin,Txpin); 
char val;

// 電壓電流
#define VT_PIN A2 // connect VT
#define AT_PIN A3// connect AT
#define ARDUINO_WORK_VOLTAGE 5.0

// Servo
Servo myservo;  // 建立SERVO物件
Servo myservo1;  // 建立SERVO物件

// LCD
LiquidCrystal_I2C lcd(0x27, 20, 2);

void setup() {
  myservo.attach(3);      // 設3腳位為X
  myservo1.attach(4);     // 設4腳位為Y
  BT.begin(9600);
  Serial.begin(9600);
  Serial.println("BT就緒");
  lcd.init();
  lcd.backlight();
  myservo.write(45);     //設X預設為45度角
  myservo1.write(135);   //設Y預設為135度角
}

void loop() {
  //LCD
  int x = analogRead(A0);
  int y = analogRead(A1);
  int v = analogRead(VT_PIN);
  int a = analogRead(AT_PIN);
  int w;
  int b=45,c=135,d=(x-y)/11;
  double voltage = v * (ARDUINO_WORK_VOLTAGE / 1023.0) * 5;
  double current = a * (ARDUINO_WORK_VOLTAGE / 1023.0);
  w=voltage*current;
  int z=0;
  z=(x+y)/2;
  // LCD顯示
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.setCursor(2, 0);
  lcd.print(voltage);
  lcd.setCursor(8, 0);
  lcd.print("A:");
  lcd.setCursor(10, 0);
  lcd.print(current);
  lcd.setCursor(0, 1);
  lcd.print("L:"); 
  lcd.setCursor(2, 1);
  lcd.print(z);
  lcd.setCursor(8, 1);
  lcd.print("W:");
  lcd.setCursor(10, 1);
  lcd.print(w);
  // 藍芽傳輸
  String data = String(voltage) + " " + String(current) + " " + String(z) + " " + String(w);
  BT.print(data);
  Sup(b,c,d,x,y);
  delay(950);
}

void Sup(int b,int c,int d,int x,int y){
  // 伺服馬達
  if(d<0){
    d=abs(d);
  }
  if((b>90)&&(c<90)){
    b=b-d;//x
    c=c+d;//y
  }
  else{
    b=b+d;//x
    c=c-d;//y
  }
  myservo.write(b); // x
  myservo1.write(c); // y
  Serial.println(d);
  delay(1000);
}