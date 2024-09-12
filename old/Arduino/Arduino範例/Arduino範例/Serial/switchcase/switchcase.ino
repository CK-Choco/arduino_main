// 從序列埠控制 LED 開關，使用switch..case

const byte LED = 13;
char val;     		// 儲存接收資料的變數，採字元類型

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("輸入1:亮燈，0:暗燈，2:閃爍");
}

void loop() {
  if( Serial.available() ) {
    val = Serial.read();
    switch (val) {
    case '0':
      digitalWrite(LED, LOW);
      Serial.print("LED OFF");
      break;
    case '1':
      digitalWrite(LED, HIGH);
      Serial.print("LED ON");
      break;
    case '2':
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
      break;  
    }
  }
}

