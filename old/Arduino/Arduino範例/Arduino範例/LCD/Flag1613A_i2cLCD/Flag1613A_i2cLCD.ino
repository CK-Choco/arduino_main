/*
 * 本範例使用 Flag1613A 來量測溫溼度值，              © 華夏科大電子系 吳宗憲      
 * 並將量測結果傳送至序列監控視窗觀察。
 * 工作電壓：DC5V 
 * FLAG1613A Temperature腳位<------->Arduino A1
 * FLAG1613A Humidity腳位<---------->Arduino A0
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int tempPin=A1, humiPin=A0;
unsigned int tempAdc,humiAdc; // 儲存讀取的ADC值

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup(void)
{
  lcd.begin(16,2);               // initialize the lcd 
  lcd.clear();
  //lcd.home ();                   // go home
  lcd.print("Hello, ARDUINO ");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print (" FORUM - fm   ");
  delay ( 3000 );
}

void loop()
{
  char humidityData[10];
  char tempData[10];

  lcd.clear();
  FLAG1613AProcessing(tempData,humidityData);
  lcd.setCursor ( 4, 0 );        // go to the next line
  lcd.print ("Temp");
  lcd.setCursor ( 9, 0 );        // go to the next line
  lcd.print (tempData);
  lcd.print ((char) 0xDF);
  lcd.print ("C");
  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print ("Humidity");
  lcd.setCursor ( 9, 1 );        // go to the next line
  lcd.print (humidityData);
  lcd.print ("%");
  delay(2000);
}

void FLAG1613AProcessing(char TD[],char HD[]) {
// 取得 A0, A1 腳位感測值, 傳回值範圍為 0~1023
  tempAdc = analogRead(tempPin);
  humiAdc = analogRead(humiPin);  
  
  dtostrf(adcToTemperature(tempAdc),5,2,TD);
  dtostrf(adcToHumidity(humiAdc),5,2,HD);  
}

// Flag-1613A 溼度感測器的『ADC=>溼度』轉換函式
// 詳見 Flag-1613A 產品手冊
byte adcToHumidity(unsigned int adc)
{
  float v = (adc/1023.0)*5;
  
  return (-0.154 + 0.3134*v + 0.00093156 *v*v*v)*100;
}

// Flag-1613A 溫度感測器的『ADC=>溫度』轉換函式
// 詳見 Flag-1613A 產品手冊
float adcToTemperature(unsigned int adc)
{
  float r= adc/(1023.0-adc) *39000;
  float t= 0.000650630554294582 + 0.00029368977366999 * log(r);
  
  return (1/t)-273.15;
}
