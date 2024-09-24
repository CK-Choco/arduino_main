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
#define CLK 25      //旋轉編碼器 CLK 連接 Arduino pin 25
#define DT  26      //旋轉編碼器 DT 連接 Arduino pin 26
#define SW  27      //旋轉編碼器 SW 連接 Arduino pin 27
int pin=2;           //定義一些整數；
int count = 0;
int lastCLK = 0;     //lastCLK 為旋轉編碼器 CLK 預設狀態 =0

void setup() {
  u8g2.begin();u8g2.enableUTF8Print();  //啟用UTF8文字的功能
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");
  pinMode(PIR_PIN, INPUT);
  //旋鈕編碼
  pinMode(SW, INPUT);      //Arduino 預備讀入旋轉編碼器 CLK, DT, and SW 狀態 
  digitalWrite(SW, HIGH);  //旋轉編碼器按鍵 SW為上拉電阻模式
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  //設置系統岔斷模式，當pin 2 輸入狀態有改變( CHANGE ) 時，呼叫副程式 ClockChanged() 
  attachInterrupt(digitalPinToInterrupt(pin), ClockChanged, CHANGE); 
}

void loop() {
  // 開機後時間
  int secs = (millis() - startTime) / 1000;
  // 濕溫度
  float temperature = 0;float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("DHT22讀取失敗, Error="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(2000);
    return;
  }
  // BT傳輸
  String data = String(temperature) + ";" + String(humidity) + ";" + String(secs);SerialBT.println(data);
  // OLED
  u8g2.setFont(u8g2_font_unifont_t_chinese1); //使用我們做好的字型
  u8g2.firstPage();
  do {
    //溫度
    u8g2.setCursor(0, 14);u8g2.print((float)temperature);
    u8g2.setCursor(45, 14);u8g2.print("*C");
    //濕度
    u8g2.setCursor(0, 35);u8g2.print((float)humidity);
    u8g2.setCursor(45, 35);u8g2.print("*RH%"); 
    //時間  
    u8g2.setCursor(0, 60);u8g2.print(secs);
    u8g2.setCursor(45, 60);u8g2.print("s");
  } while ( u8g2.nextPage() );
  // 紅外
  int moving = digitalRead(PIR_PIN); //讀取D4是否有偵測到物體移動
  if(moving==HIGH){ //如果有物體移動
    Serial.println("有東西在動！");
    delay(2000);  
  }else{
    Serial.println("瞎了！"); 
    } 
  // Debug
  
  Serial.println("=================================");
  Serial.print("樣品 OK ");
  Serial.print((float)temperature); Serial.print(" C, ");
  Serial.print((float)humidity); Serial.print(" RH%, ");
  Serial.print(secs); Serial.println(" s");
  
  
  delay(1000);
}

void OLEDOutput(int value)   
{
  if (value >= 1 && value <= 10) {
    switch(value) {
      case 1: 
        
        break;
      case 2:
        
        break;
      case 3:
        
        break;
      case 4:
        
        break;
     case 5:
        
        break;
      case 6:
        
        break;
      case 7:
        
        break;
      case 8:
        
        break;
      case 9:
             
        break;   
      case 10:
               
        break;           
    }
  }
}

void ClockChanged() 
{   
  int clkValue = digitalRead(CLK);
  int dtValue = digitalRead(DT);  
  if (lastCLK != clkValue)
  {
    lastCLK = clkValue;
    count += (clkValue != dtValue ? 1 : -1); 

    Serial.print("count:");
    Serial.println(count);
    int rcount = count/2;  
    OLEDOutput(rcount); 
  }
}
