#include <BluetoothSerial.h>  // 藍芽

// 藍芽
BluetoothSerial SerialBT;

// 電壓電流
#define VT0_PIN 34
#define AT0_PIN 35
#define VT1_PIN 36
#define AT1_PIN 39
#define ARDUINO_WORK_VOLTAGE 5.0

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32_BT");
}

void loop() {
}
