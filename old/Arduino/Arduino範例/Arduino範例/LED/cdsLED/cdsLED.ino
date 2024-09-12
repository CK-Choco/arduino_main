// 使用光敏電阻製作小夜燈

const byte LED = 13;
const byte CdS = A0;

void setup() {
  pinMode(LED, OUTPUT) ;
}
void loop() {
  int val;
  val = analogRead(CdS) ;
  if (val >= 700) {
    digitalWrite(13, HIGH) ;
  } else if (val < 600) {		// 設定低於600時，再關閉燈光。
	  digitalWrite(13, LOW) ;
  }
}

