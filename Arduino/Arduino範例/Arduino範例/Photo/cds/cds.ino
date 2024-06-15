/* 
      光敏電阻範例                     © 華夏科大電子系 吳宗憲
      可搭配ABB Car 操作，成為啟動器
*/
#include <Servo.h>                           // Include servo library
 
#define photoresPin 0                      // define the value of photoresistor pin
int sensorValue = 0;
 
void setup()                                 // Built-in initialization block
{ 
  pinMode(photoresPin, INPUT);               // Set photoresistor pin to input
  
  Serial.begin(9600);                        // RS-232 baud rate
}  
 
void loop()                                  // Main loop auto-repeats
{  
  // 多次讀取接腳的類比訊號值
  //sensorValue = 0.5*sensorValue+0.5*analogRead(photoresPin);
  sensorValue = analogRead(photoresPin);
  Serial.print("Value = ");
  Serial.println(sensorValue);
  delay(1000);
}//end loop 

