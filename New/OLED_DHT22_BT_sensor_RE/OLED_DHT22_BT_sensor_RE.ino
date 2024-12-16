#include <Arduino.h>
#include <U8g2lib.h>
#include <SimpleDHT.h>
#include <BluetoothSerial.h>

//LED
int led_pin = 2;

// BT
BluetoothSerial SerialBT; 

// OLED
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// 濕溫度
int pinDHT22 = 13;  //濕溫度連接 ESP32 pin 13
SimpleDHT22 dht22(pinDHT22);

// 時間
unsigned long startTime = millis();

// 紅外
#define PIR_PIN 23   //紅外連接 ESP32 pin 23

// 旋鈕編碼
#define CLK 25      //旋轉編碼器 CLK 連接 ESP32 pin 25
#define DT  26      //旋轉編碼器 DT 連接 ESP32 pin 26
#define SW  27      //旋轉編碼器 SW 連接 ESP32 pin 27
int pin=25;         //CLK發生改變的觸發腳
int count = 0;
int lastCLK = 0;     //lastCLK 為旋轉編碼器 CLK 預設狀態 =0
int currentPage = 1; // 追踪當前顯示的頁面

// 繼電器
int relayPin = 4; //繼電器連接 ESP32 pin 4

// 電壓電流
const int VT_PIN = 36; //連接 ESP32 pin 36
const int AT_PIN = 39; //連接 ESP32 pin 39
const int BVT_PIN = 34; //連接 ESP32 pin 34
const int BAT_PIN = 35; //連接 ESP32 pin 35
#define WORK_VOLTAGE 4.3

// 光敏
#define Ph_pin 32 // 光敏連接 ESP32 pin 32

void setup() {
  u8g2.begin(); u8g2.enableUTF8Print();  //啟用UTF8文字的功能
  Serial.begin(115200);
  Serial.println("初始化");
  SerialBT.begin("ESP32_BT"); //藍芽名稱
  pinMode(VT_PIN, INPUT);
  pinMode(AT_PIN, INPUT);
  pinMode(BVT_PIN, INPUT);
  pinMode(BAT_PIN, INPUT);
  pinMode(PIR_PIN, INPUT); //紅外
  pinMode(relayPin, OUTPUT); //繼電器
  //旋鈕編碼
  pinMode(SW, INPUT);      
  digitalWrite(SW, HIGH);  //旋轉編碼器按鍵 SW為上拉電阻模式
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  // 只要pin發生改變，觸發執行ClockChanged
  attachInterrupt(digitalPinToInterrupt(pin), ClockChanged, CHANGE); 
  pinMode(led_pin, OUTPUT);
}

void loop() {
  
  // 開機後時間
  int secs = (millis() - startTime) / 1000;

  // 光敏
  int y = 0; y = analogRead(Ph_pin);
  double L = (4095 - y)/4; //ESP32=>4095 Arduino=>1023
  
  // 電源-電壓電流
  int v = analogRead(VT_PIN);
  int a = analogRead(AT_PIN);
  // WORK_VOLTAGE=>工作電壓 5V
  float voltage = v * (WORK_VOLTAGE / 1023); 
  float current = a * (WORK_VOLTAGE / 1023); 
  int w =  voltage*current;

  // 電池-電壓電流
  int bv = analogRead(BVT_PIN);
  int ba = analogRead(BAT_PIN);
  float bvoltage = bv * (WORK_VOLTAGE / 1023); 
  float bcurrent = ba * (WORK_VOLTAGE / 1023); 
  int bw =  bvoltage*bcurrent;
 
  // 濕溫度
  float temperature = 0, humidity = 0; //DHT22
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    //Serial.print("Read DHT22 failed, err="); Serial.print(SimpleDHTErrCode(err));
    //Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); 
    delay(500);
    return;
  }
  
  // BT傳輸(電源-電壓電流瓦數=>電池-電壓電流瓦數=>日照溫度濕度)
  String data = String (voltage) + ";" + String (current) + ";" + String (w) + ";" + String (bvoltage) + ";" + String (bcurrent) + ";" + String (bw) + ";" + String (L) + ";" + String (temperature) + ";" + String (humidity) + ";";
  SerialBT.println(data);
  
  // 紅外
  int moving = digitalRead(PIR_PIN);
  if (L < 300){
    if (moving == 1) { 
      digitalWrite(relayPin, HIGH); 
      digitalWrite(led_pin, HIGH);
    } else {
      digitalWrite(relayPin, LOW);
      digitalWrite(led_pin, LOW);
    }
  } else {
      digitalWrite(relayPin, LOW);
      digitalWrite(led_pin, LOW);
  }
  
  // 更新OLED
  OLEDOutput(currentPage, temperature, humidity, secs, voltage, current, w, bvoltage, bcurrent, bw, L);
  
  // 序列監控視窗Debug
  Debug(temperature, humidity, voltage, current, w, bvoltage, bcurrent, bw, L, y, v);
  
  delay(750); //暫停0.75秒
}

void Debug(float temperature, float humidity, double voltage, double current, int w, double bvoltage, double bcurrent, int bw, int L, int y, int v){
  Serial.println("=================================");
  Serial.print("日照:"); Serial.print(L);
  Serial.print("最大光偶:"); Serial.print(y);
  Serial.print("溫度:"); Serial.print((float)temperature);
  Serial.print("濕度:"); Serial.println((float)humidity);
  Serial.println("v電源:"); Serial.println(v);
  Serial.println("電源:"); Serial.println(voltage); Serial.println(current); Serial.println(w);
  Serial.println("電池:"); Serial.println(bvoltage); Serial.println(bcurrent); Serial.println(bw);
  }

void OLEDOutput(int page, float temperature, float humidity, int secs, double voltage, double current, int w, double bvoltage, double bcurrent, int bw, int L) {
  u8g2.setFont(u8g2_font_unifont_t_chinese1); // 設置字型
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
      u8g2.setCursor(0, 50); u8g2.print("瓦數"); u8g2.setCursor(45, 50); u8g2.print(w);
    } else if (page == 3) {
      // 第三頁
      u8g2.setCursor(0, 14); u8g2.print("b電壓"); u8g2.setCursor(45, 14); u8g2.print(bvoltage);
      u8g2.setCursor(0, 32); u8g2.print("b電流"); u8g2.setCursor(45, 32); u8g2.print(bcurrent); 
      u8g2.setCursor(0, 50); u8g2.print("b瓦數"); u8g2.setCursor(45, 50); u8g2.print(bw);
    } else if (page == 4) {
      // 第四頁
      u8g2.setCursor(0, 14); u8g2.print("日照"); u8g2.setCursor(45, 14); u8g2.print(L);
      u8g2.setCursor(0, 32); u8g2.print(" "); u8g2.setCursor(45, 32); u8g2.print(" "); 
      u8g2.setCursor(0, 50); u8g2.print(" "); u8g2.setCursor(45, 50); u8g2.print(" ");
    }
  } while (u8g2.nextPage());
}

void ClockChanged() {   
  int clkValue = digitalRead(CLK);
  int dtValue = digitalRead(DT);  
  if (lastCLK != clkValue) {
    lastCLK = clkValue;
    // 根據旋轉放向上下頁
    currentPage += (clkValue != dtValue ? -1 : 1); 
    // 確保當前頁面在有效範圍
    currentPage = constrain(currentPage, 1, 4);
  }
}
