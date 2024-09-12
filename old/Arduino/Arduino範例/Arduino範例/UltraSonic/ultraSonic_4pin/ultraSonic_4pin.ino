/* 
      4pin 超音波範例                     © 華夏科大電子系 吳宗憲
      可搭配ABB Car 操作，成為超音波自走車
*/
const byte trigPin = 10;  // 超音波模組的觸發腳
const byte echoPin = 9;    // 超音波模組的接收腳
// const byte echoPin = A5;
unsigned long d;          // 儲存高脈衝的持續時間

unsigned long ping() {
  digitalWrite(trigPin, HIGH);   // 觸發腳設定成高電位
  delayMicroseconds(10);         // 持續 10 微秒
  digitalWrite(trigPin, LOW);    // 觸發腳設定成低電位
 
  return pulseIn(echoPin, HIGH); // 傳回高脈衝的持續時間
}

void setup() {
  pinMode(trigPin, OUTPUT);  // 觸發腳設定成「輸出」
  pinMode(echoPin, INPUT);   // 接收腳設定成「輸入」
 
  Serial.begin(9600);        // 初始化序列埠
}
void loop(){
  d = ping() / 58;       // 把高脈衝時間值換算成公分單位
  Serial.print("distance = ");
  Serial.print(d);       // 顯示距離
  Serial.print("cm");
  Serial.println();
  delay(500);          // 等待一秒鐘（每隔一秒測量一次）
}
