/* 
      藍牙 + stdServo 範例                     © 華夏科大電子系 吳宗憲
*/
//藍牙的TX腳位請連結------Arduino 的D10腳位
//藍牙的RX腳位請連結------Arduino 的D11腳位 (可空接)
//伺服馬達腳位請連結------Arduino 的D9腳位

#include <Servo.h>  
#include <SoftwareSerial.h>
const byte Txpin=255; //空接
const byte Rxpin=10;
SoftwareSerial mySerial = SoftwareSerial(Rxpin,Txpin);
Servo servo1;  

void servoRotation(){
  for (int i = 30; i<= 150; i += 2){
    servo1.write(i);
    delay(20);
  }
}

void setup() 
{ 
  servo1.attach(9);  
  mySerial.begin(9600);   
  //Serial.begin(9600);
  servo1.write(90);
}  

void loop() 
{ 
  byte btIn;
  if (mySerial.available())
  {
    btIn = mySerial.read(); 
    if (btIn)
      servo1.write(btIn);
    else
      servoRotation();
  }
  delay(20);
}
