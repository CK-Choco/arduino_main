/*
 * 本範例使用 DHT11 來量測溫溼度值，              © 華夏科大電子系 吳宗憲      
 * 並將量測結果傳送至序列監控視窗觀察。
 * 工作電壓：DC5V
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
#include <dht11.h>
#define DHT11PIN 5  //溫度感測器 DHT-11 連接D5

dht11 DHT11;
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup(void)
{
  lcd.begin(16,2);               // initialize the lcd 
  lcd.clear();
  //lcd.home ();                   // go home
  lcd.print("Hello, ARDUINO ");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print (" FORUM - fm   ");
  delay ( 5000 );
}

void loop()
{
  lcd.clear();
  char humidityData[10];
  char tempData[10];
  
  DHT11Processing(humidityData,tempData);
  lcd.setCursor ( 4, 0 );
  lcd.print("Temp");
  lcd.setCursor ( 9, 0 );
  lcd.print(tempData);
  lcd.print((char)0xDF);
  lcd.print("C");
  lcd.setCursor ( 0, 1 );
  lcd.print("Humidity");
  lcd.setCursor ( 9, 1 );
  lcd.print(humidityData);
  lcd.print("%");
  delay(2000);
}

void DHT11Processing(char HD[], char TD[]){
  int chk = DHT11.read(DHT11PIN);
    
  if (chk == 0) {
    dtostrf((float)DHT11.humidity,5,2,HD);
    dtostrf((float)DHT11.temperature,5,2,TD);
  }// end if
  else {
    Serial.println("DHT11 Error");
  }
}
