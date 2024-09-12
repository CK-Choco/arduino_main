/*
 * © 華夏科大電子系 吳宗憲
 * 本範例練習 Arduino 超音波距離 <--> Android 手機藍牙APP
 * 工作電壓：5V
 */
//藍牙的TX腳位請連結------Arduino 的D10腳位
//藍牙的RX腳位請連結------Arduino 的D11腳位

#include <SoftwareSerial.h>
const byte Txpin=11;
const byte Rxpin=10;
SoftwareSerial BT(Rxpin,Txpin); 

const byte trigPin = 9;  // 超音波模組的觸發腳    
const byte echoPin = A5; // 超音波模組的接收腳

void setup() 
{ 
  BT.begin(9600);   
  Serial.begin(9600);
 
  pinMode(trigPin, OUTPUT);  // 觸發腳設定成「輸出」
  pinMode(echoPin, INPUT);   // 接收腳設定成「輸入」
}  

void loop() 
{ 
  char distance[10];
  String cmd;
  unsigned long d;
  
  d = ping() / 58;  
  
  if (BT.available()){
    Serial.println("BT is OK");
  }
    itoa(d,distance,10); 
    cmd = "d," + (String)distance;
    BT.print(cmd);
    Serial.println(cmd);
  delay(1000);
}

unsigned long ping() {
  digitalWrite(trigPin, HIGH);   // 觸發腳設定成高電位
  delayMicroseconds(10);         // 持續 10 微秒
  digitalWrite(trigPin, LOW);    // 觸發腳設定成低電位
 
  return pulseIn(echoPin, HIGH); // 傳回高脈衝的持續時間
}

