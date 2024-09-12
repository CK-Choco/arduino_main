/*
 * 藍牙RGB LED範例                     © 華夏科大電子系 吳宗憲
 * 搭配藍牙手機APP來控制(BT_RGB_led.aia 或SoundControlLED.aia)
 */
//藍牙的TX腳位請連結------Arduino 的D2腳位
//藍牙的RX腳位請連結------Arduino 的D3腳位
#include <SoftwareSerial.h>

#define Rx        2
#define Tx        3
#define bluePin   9
#define greenPin 10
#define redPin   11

SoftwareSerial BT(Rx, Tx);
byte RGB[3];

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
}

void loop() {
  if (BT.available() >= 3) {
    Serial.println(BT.available());
    BT.readBytes(RGB, 3);
    
    Serial.print("R = ");
    Serial.print(RGB[0]);
    Serial.print(", G = ");
    Serial.print(RGB[1]);
    Serial.print(", B = ");
    Serial.println(RGB[2]);
    
    analogWrite(redPin, RGB[0]);
    analogWrite(greenPin, RGB[1]);
    analogWrite(bluePin, RGB[2]);
  }
}
