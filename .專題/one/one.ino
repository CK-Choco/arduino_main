// 程式庫
#include <Wire.h> // I2C程式庫
#include <LiquidCrystal_I2C.h> // LCD_I2C模組程式庫

LiquidCrystal_I2C lcd(0x27, 20, 2); // LCD I2C位址，默認為0x27或0x3F，依據背板的晶片不同而有差異，16、2為LCD顯示器大小。

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);
  int z=0;
  z=x-y;
  Serial.println("X:");
  Serial.println(x);
  Serial.println("Y:");
  Serial.println(y);
  Serial.println("Z:");
  Serial.println(z);
  //Serial.println(z);

  lcd.clear();
  lcd.setCursor(0, 0); // (colum, row)從第一排的第三個位置開始顯示
  lcd.print("X:");
  lcd.setCursor(3, 0);
  lcd.print(x);
  lcd.setCursor(8, 0);
  lcd.print("Y:");
  lcd.setCursor(10, 0);
  lcd.print(y);
  //lcd.print("Light:"); 
  lcd.setCursor(0, 1); // (colum,row)從第二排第三格位置開始顯示
  lcd.print(z);
  
  delay(500);

}
