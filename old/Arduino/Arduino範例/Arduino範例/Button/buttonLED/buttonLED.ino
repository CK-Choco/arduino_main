/* button + LED 範例               © 華夏科大電子系 吳宗憲
 *  + 序列監控視窗顯示bouncing
 */
const byte inPin = 10;               // 按鍵連接腳位
const byte ledPin = 13;               // LED連接腳位
byte val = 0;
byte sTop = 0;                       // 按下按鍵

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);           // 設定LED腳位為輸出
  pinMode(inPin, INPUT);             // 設定按鍵腳位為輸入 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(inPin);         // 讀取按鍵狀態
  if (val){                         // 如果按鍵按下
    sTop += 1;
    Serial.println(sTop);
    digitalWrite(ledPin,HIGH);       // LED 亮
  }
  else
    digitalWrite(ledPin,LOW);        // LED 暗

  delay(100);
}
