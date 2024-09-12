#include <BluetoothSerial.h> 
BluetoothSerial SerialBT; 

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT"); //藍牙顯示名稱，可自行更改，需避免與他人重複命名
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.println(SerialBT.readString());
  }
  delay(50);
}
