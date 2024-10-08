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
int pinDHT22 = 13;  //濕溫度OUT腳
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
// 繼電器
int relayPin = 4;
// 電壓電流
#define VT_PIN 16
#define AT_PIN 17
#define BVT_PIN 18
#define BAT_PIN 19
#define ARDUINO_WORK_VOLTAGE 5.0

void setup() {
  u8g2.begin(); u8g2.enableUTF8Print();  //啟用UTF8文字的功能
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");
  pinMode(VT_PIN, INPUT);
  pinMode(AT_PIN, INPUT);
  pinMode(BVT_PIN, INPUT);
  pinMode(BAT_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
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
  // 電源-電壓電流
  int v = analogRead(VT_PIN);
  int a = analogRead(AT_PIN);
  // 電池-電壓電流
  int bv = analogRead(BVT_PIN);
  int ba = analogRead(BAT_PIN);
  int w,bw,z=0;
  double voltage = v * (ARDUINO_WORK_VOLTAGE / 1024) * 5; 
  double current = a * (ARDUINO_WORK_VOLTAGE / 1024); 
  w =  voltage*current;
  double bvoltage = bv * (ARDUINO_WORK_VOLTAGE / 1024) * 5; 
  double bcurrent = ba * (ARDUINO_WORK_VOLTAGE / 1024); 
  bw =  bvoltage*bcurrent;
  // 濕溫度
  //byte temperature = 0, humidity = 0; //DHT11
  float temperature = 0, humidity = 0; //DHT22
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  
  // BT傳輸(電源-電壓電流瓦數=>電池電壓電流瓦數=>日照溫度濕度)
  String data = String (voltage) + ";" + String (current) + ";" + String (w) + ";" + String (bvoltage) + ";" + String (bcurrent) + ";" + String (bw) + ";" + String (z) + ";" + String (temperature) + ";" + String (humidity);
  SerialBT.println(data);
  
  // 紅外
  int moving = digitalRead(PIR_PIN);
  if (moving == HIGH) { 
    //Serial.println("有人");
    digitalWrite(relayPin, LOW);
    //delay(2000);  
  } else {
    //Serial.println("沒人！"); 
    digitalWrite(relayPin, HIGH);
  }
  
//Debug
  Serial.println("=================================");
  //Serial.print((float)temperature); Serial.print(" C, ");
  //Serial.print((float)humidity); Serial.print(" RH%, ");
  //Serial.println(" s");
  Serial.println("電源:"); Serial.println(voltage); Serial.println(current); Serial.println(w);
  Serial.println("電池:"); Serial.println(bvoltage); Serial.println(bcurrent); Serial.println(bw);

  // 更新OLED
  OLEDOutput(currentPage, temperature, humidity, secs, voltage, current, w, bvoltage, bcurrent, bw);
  
  delay(750);
}

void OLEDOutput(int page, float temperature, float humidity, int secs, double voltage, double current, int w, double bvoltage, double bcurrent, int bw) {
  u8g2.setFont(u8g2_font_unifont_t_chinese1); // 使用字型
  u8g2.firstPage();
  do {
    if (page == 1) {
      // 第一頁
      u8g2.setCursor(0, 14); u8g2.print("溫度"); u8g2.setCursor(45, 14); u8g2.print(temperature);
      u8g2.setCursor(0, 32); u8g2.print("濕度"); u8g2.setCursor(45, 32); u8g2.print(humidity); 
      u8g2.setCursor(0, 50); u8g2.print("時間"); u8g2.setCursor(45, 50); u8g2.print(secs);
    } else if (page == 2) {
      // 第二頁
      u8g2.setCursor(0, 14); u8g2.print("電壓"); u8g2.setCursor(45, 14); u8g2.print(voltage);
      u8g2.setCursor(0, 32); u8g2.print("電流"); u8g2.setCursor(45, 32); u8g2.print(current); 
      u8g2.setCursor(0, 50); u8g2.print("W"); u8g2.setCursor(45, 50); u8g2.print(w);
    } else if (page == 3) {
      // 第三頁
      u8g2.setCursor(0, 14); u8g2.print("b電壓"); u8g2.setCursor(45, 14); u8g2.print(bvoltage);
      u8g2.setCursor(0, 32); u8g2.print("b電流"); u8g2.setCursor(45, 32); u8g2.print(bcurrent); 
      u8g2.setCursor(0, 50); u8g2.print("bW"); u8g2.setCursor(45, 50); u8g2.print(bw);
    }
  } while (u8g2.nextPage());
}

void ClockChanged() {   
  int clkValue = digitalRead(CLK);
  int dtValue = digitalRead(DT);  
  if (lastCLK != clkValue) {
    lastCLK = clkValue;
    // 根據旋轉放向上下頁
    currentPage += (clkValue != dtValue ? 1 : -1); 
    // 確保當前頁面在有效範圍
    currentPage = constrain(currentPage, 1, 3);

    Serial.print("Current Page: ");
    Serial.println(currentPage);
  }
}
