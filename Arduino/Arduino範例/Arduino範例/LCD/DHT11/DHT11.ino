/*
 * 本範例使用 DHT11 來量測溫溼度值，              © 華夏科大電子系 吳宗憲      
 * 並將量測結果傳送至序列監控視窗觀察。
 * 工作電壓：DC5V
 */
#include <dht11.h>
#define DHT11PIN 5  //溫度感測器 DHT-11 連接D5

dht11 DHT11;

void setup(void)
{
  Serial.begin(9600);
}

void loop()
{
  char humidityData[10];
  char tempData[10];
  
  DHT11Processing(humidityData,tempData);
  Serial.print(humidityData);
  Serial.print("   ");
  Serial.println(tempData);
  delay(2000);
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
