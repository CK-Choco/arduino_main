/*
 * 本範例使用 FLAG1613A 來量測溫溼度值，              © 華夏科大電子系 吳宗憲      
 * 並將量測結果透過藍牙傳送至手機APP觀察。
 * 工作電壓：DC5V
 * FLAG1613A Temperature腳位<------->Arduino A1
 * FLAG1613A Humidity腳位<---------->Arduino A0
 * 藍牙的TX腳位請連結<------>Arduino 的D10腳位
 * 藍牙的RX腳位請連結<------>Arduino 的D11腳位
 */
#include <dht11.h>
#include <SoftwareSerial.h>
#define DHT11PIN 5  //溫度感測器 DHT-11 連接D5

const int Txpin=11;
const int Rxpin=10;

dht11 DHT11;
SoftwareSerial BT = SoftwareSerial(Rxpin,Txpin);

void setup() {
  BT.begin(9600);
  Serial.begin(9600);
}

void loop() {
  char humidityData[10] = {};
  char tempData[10] = {};
    
  DHT11Processing(humidityData,tempData);
  sendDATA(tempData,humidityData);
  
  delay(3000); // 每3秒更新一次
}
void sendDATA(String T,String H) {
  String cmd;

  cmd = T+" , "+H;
  //cmd = "Temperature = "+T+" , "+"Humidity = "+H;
  BT.print(cmd);
  Serial.println(cmd);
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
