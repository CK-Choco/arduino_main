// 從序列埠監控視窗觀察變數值

const byte ledPin = 13;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello," );  
  Serial.print("\tLED pin is: ");
  Serial.print(ledPin);
  Serial.print("\nBYE!");
}

void loop() {
}
