/*從序列埠控制 LED 開關
 * 1: on ; 0: off
 */

const byte LED = 13;
char val;     		// 儲存接收資料的變數，採字元類型
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.print("1: on ; 0: off!");
}

void loop() {
  if( Serial.available() ) {
    val = Serial.read();
    if (val == '1') {
      digitalWrite(LED, HIGH);
      Serial.print("LED ON");
    } 
    else if (val == '0') {
      digitalWrite(LED, LOW);
      Serial.print("LED OFF");
    }
  }
}
