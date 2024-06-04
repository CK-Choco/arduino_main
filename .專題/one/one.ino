// 程式庫
#include <Wire.h> // I2C函式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C函式庫
#include <Servo.h> // 伺服馬達函式庫
// Servo
Servo myservo;  // 建立SERVO物件
Servo myservo1;  // 建立SERVO物件
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
// LCD
LiquidCrystal_I2C lcd(0x27, 20, 2);

void setup() {
  myservo.attach(3);
  myservo1.attach(4);
  BT.begin(9600);
  Serial.begin(9600);
  Serial.println("BT就緒");
  lcd.init();
  lcd.backlight();
}

void loop() {
  //LCD
  int x = analogRead(A0);
  int y = analogRead(A1);
  int v = analogRead(VT_PIN);
  int a = analogRead(AT_PIN);
  int w;
  double voltage = v * (ARDUINO_WORK_VOLTAGE / 1023.0) * 5;
  double current = a * (ARDUINO_WORK_VOLTAGE / 1023.0);
  w=voltage*current;
  int lz=0;
  lz=x-y;
  int z=0;
  int z1=0;
  z1=x+y;
  z=z1/2;
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
  // 伺服馬達
  int s=90;
  int s1,s2;
  s1=s-lz;
  s2=s+lz;
  myservo.write(s1);
  myservo1.write(s2);
  delay(950);
}
