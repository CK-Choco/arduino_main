// 程式庫
#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫
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
LiquidCrystal_I2C lcd(0x27, 20, 2); // LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。

void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  Serial.println("BT就緒");
  lcd.init();
  lcd.backlight();
}

void loop() {
  //BT
  if (BT.available()){
    val = BT.read();
    Serial.print(val);
  }

  if (Serial.available()){
    val = Serial.read();
    Serial.print(val);
    BT.print(val);
  }
  //LCD
  int x = analogRead(A0);
  int y = analogRead(A1);
  int v = analogRead(VT_PIN);
  int a = analogRead(AT_PIN);
  int w;
  double voltage = v * (ARDUINO_WORK_VOLTAGE / 1023.0) * 5;
  double current = a * (ARDUINO_WORK_VOLTAGE / 1023.0);
  w=voltage*current;
  int z=0;
  int z1=0;
  z1=x+y;
  z=z1/2;
  //z=x-y;
  // Serial顯示
  //Serial.println("X:");
  //Serial.println(x);
  //Serial.println("Y:");
  //Serial.println(y);
  //Serial.println("Z:");
  //Serial.println(z);
  // LCD顯示
  lcd.clear();
  lcd.setCursor(0, 0); // (colum, row)從第一排的第三個位置開始顯示
  lcd.print("V:");
  lcd.setCursor(2, 0);
  lcd.print(voltage);
  lcd.setCursor(8, 0);
  lcd.print("A:");
  lcd.setCursor(10, 0);
  lcd.print(current);
  lcd.setCursor(0, 1); // (colum,row)從第二排第三格位置開始顯示
  lcd.print("L:"); 
  lcd.setCursor(2, 1); // (colum,row)從第二排第三格位置開始顯示
  lcd.print(z);
  lcd.setCursor(8, 1);
  lcd.print("W:");
  lcd.setCursor(10, 1);
  lcd.print(w);
  
  delay(500);

}
