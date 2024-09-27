#include <Arduino.h>
#include <U8g2lib.h>
#include <SimpleDHT.h>
#include <BluetoothSerial.h>

// BT
BluetoothSerial SerialBT; 
// OLED
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
// 濕溫度
int pinDHT22 = 15;  //濕溫度OUT腳
SimpleDHT22 dht22(pinDHT22);
// 時間
unsigned long startTime = millis();
// 紅外
#define PIR_PIN 23   //紅外OUT腳
// 旋鈕編碼
#define CLK 25      //旋轉編碼器 CLK 連接 ESP32 pin 25
#define DT  26      //旋轉編碼器 DT 連接 ESP32 pin 26
#define SW  27      //旋轉編碼器 SW 連接 ESP32 pin 27
int pin=25;           //定義一些整數；
int count = 0;
int lastCLK = 0;     //lastCLK 為旋轉編碼器 CLK 預設狀態 =0
int currentPage = 1; // 追踪當前顯示的頁面
// 電壓電流
#define VT_PIN 16
#define AT_PIN 17
#define ARDUINO_WORK_VOLTAGE 5.0

void setup() {
  u8g2.begin(); u8g2.enableUTF8Print();  //啟用UTF8文字的功能
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");
  pinMode(PIR_PIN, INPUT);
  //旋鈕編碼
  pinMode(SW, INPUT);      
  digitalWrite(SW, HIGH);  //旋轉編碼器按鍵 SW為上拉電阻模式
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin), ClockChanged, CHANGE); 
}

void loop() {
  // 開機後時間
  int secs = (millis() - startTime) / 1000;
  // 電壓電流
  int v = analogRead(VT_PIN);
  int a = analogRead(AT_PIN);
  int w;
  double voltage = v * (ARDUINO_WORK_VOLTAGE / 1024) * 5; double current = a * (ARDUINO_WORK_VOLTAGE / 1024); w =  voltage*current;
  // 濕溫度
  float temperature = 0, humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("DHT22讀取失敗, Error="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); 
    delay(2000);
    return;
  }
  
  // BT傳輸
  String data = String(temperature) + ";" + String(humidity) + ";" + String(secs) + ";" + String(voltage) + ";" + String(current) + ";" + String(w);
  SerialBT.println(data);
  
  // 紅外
  int moving = digitalRead(PIR_PIN);
  if (moving == HIGH) { 
    Serial.println("有東西在動！");
    //delay(2000);  
  } else {
    Serial.println("瞎了！"); 
  }
  
  // Debug
  Serial.println("=================================");
  Serial.print("樣品 OK ");
  Serial.print((float)temperature); Serial.print(" C, ");
  Serial.print((float)humidity); Serial.print(" RH%, ");
  Serial.print(secs); Serial.println(" s");

  // 更新OLED
  OLEDOutput(currentPage, temperature, humidity, secs, voltage, current, w);
  
  delay(750);
}

void OLEDOutput(int page, float temperature, float humidity, int secs, double voltage, double current, int w) {
  u8g2.setFont(u8g2_font_unifont_t_chinese1); // 使用字型
  u8g2.firstPage();
  do {
    if (page == 1) {
      // 顯示當前數據
      u8g2.setCursor(0, 14); u8g2.print("溫度"); u8g2.setCursor(45, 14); u8g2.print(temperature);
      u8g2.setCursor(0, 32); u8g2.print("濕度"); u8g2.setCursor(45, 32); u8g2.print(humidity); 
      u8g2.setCursor(0, 50); u8g2.print("時間"); u8g2.setCursor(45, 50); u8g2.print(secs);
    } else if (page == 2) {
      // 顯示標題
      u8g2.setCursor(0, 14); u8g2.print("電壓"); u8g2.setCursor(45, 14); u8g2.print(voltage);
      u8g2.setCursor(0, 32); u8g2.print("電流"); u8g2.setCursor(45, 32); u8g2.print(current); 
      u8g2.setCursor(0, 50); u8g2.print("W"); u8g2.setCursor(45, 50); u8g2.print(w);
    }
  } while (u8g2.nextPage());
}

void ClockChanged() {   
  int clkValue = digitalRead(CLK);
  int dtValue = digitalRead(DT);  
  if (lastCLK != clkValue) {
    lastCLK = clkValue;
    // 根据旋转方向更新页面
    currentPage += (clkValue != dtValue ? 1 : -1); 
    // 确保当前页面在有效范围内
    if (currentPage < 1) currentPage = 1;
    if (currentPage > 2) currentPage = 2;

    Serial.print("Current Page: ");
    Serial.println(currentPage);
  }
}
