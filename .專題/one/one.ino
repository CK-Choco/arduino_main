// 程式庫
#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫

#define VT_PIN A2 // connect VT
#define AT_PIN A3// connect AT
#define ARDUINO_WORK_VOLTAGE 5.0

LiquidCrystal_I2C lcd(0x27, 20, 2); // LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);
  int v = analogRead(VT_PIN);
  int a = analogRead(AT_PIN);
  int w;
  double voltage = v * (ARDUINO_WORK_VOLTAGE / 1023.0) * 5;
  double current = a * (ARDUINO_WORK_VOLTAGE / 1023.0);
  w=voltage*current;
  int z=0;
  z=x-y;
  // Serial顯示
  Serial.println("X:");
  Serial.println(x);
  Serial.println("Y:");
  Serial.println(y);
  Serial.println("Z:");
  Serial.println(z);
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
