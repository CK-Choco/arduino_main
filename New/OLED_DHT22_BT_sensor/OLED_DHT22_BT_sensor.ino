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
int pinDHT22 = 15;  //OUT腳
SimpleDHT22 dht22(pinDHT22);
// 時間
unsigned long startTime = millis();
int secs;
// 紅外
int sensor = 9;   //OUT腳

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();  //啟用UTF8文字的功能
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT");
  pinMode(sensor, INPUT);
}

void loop() {
  // 開機後時間
  secs = (millis() - startTime) / 1000;
  // 濕溫度
  float temperature = 0;float humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("DHT22讀取失敗, Error="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(2000);
    return;
  }
  // BT傳輸
  String data = String(temperature) + ";" + String(humidity) + ";" + String(secs);
  SerialBT.println(data);
  // OLED
  u8g2.setFont(u8g2_font_unifont_t_chinese1); //使用我們做好的字型
  u8g2.firstPage();
  do {
    //溫度
    u8g2.setCursor(0, 14);
    u8g2.print((float)temperature);
    u8g2.setCursor(45, 14);
    u8g2.print("*C");
    //濕度
    u8g2.setCursor(0, 35);
    u8g2.print((float)humidity);
    u8g2.setCursor(45, 35);
    u8g2.print("*RH%"); 
    //時間  
    u8g2.setCursor(0, 60);
    u8g2.print(secs);
    u8g2.setCursor(45, 60);
    u8g2.print("s");
  } while ( u8g2.nextPage() );
  // 紅外
  int moving = digitalRead(sensor); //讀取D9是否有偵測到物體移動
  if(moving==1){ //如果有物體移動
    Serial.println("有東西在動！");  
  }
  // Debug
  /*
  Serial.println(=================================);
  Serial.print(樣品 OK );
  Serial.print((float)temperature); Serial.print( C, );
  Serial.print((float)humidity); Serial.print( RH%, );
  Serial.print(secs); Serial.println( s);
  */
  delay(1000);
}
