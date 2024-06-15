/* 
      藍牙範例                     © 華夏科大電子系 吳宗憲
      本範例可用 AT Command 來設定藍牙 HC-06
      可搭配ABB Car 操作，成為藍牙遙控車
*/
//藍牙的TX腳位請連結------Arduino 的D10腳位
//藍牙的RX腳位請連結------Arduino 的D11腳位

#include <SoftwareSerial.h>
const byte Txpin=11;
const byte Rxpin=10;
SoftwareSerial BT(Rxpin,Txpin); 
char val;

void setup() 
{ 
  BT.begin(9600);   
  Serial.begin(9600);
  Serial.println("BT is ready");
}  
void loop() 
{ 
  if (BT.available()){
    val = BT.read();
    Serial.print(val);
  }

  if (Serial.available()){
    val = Serial.read();
    Serial.print(val);
    BT.print(val);
  }
}
