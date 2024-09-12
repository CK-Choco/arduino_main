// 從序列埠讀取「類比輸入」值。
#define bluePin   9
#define greenPin 10
#define redPin   11
const byte potPin = A0;

int val;       // 接收類比輸入值的變數，類型為整數
void setup() {
  Serial.begin(9600);  // 以 9600bps 速率初始化序列埠
}
void loop() {
  val = analogRead(potPin);
  val = map(val, 0, 1023, 1, 6);
  switch (var) {
  case 1: // 紅
    LED(255,0,0);
    break;
  case 2: // 澄
    LED(255,165,0);
    break;
  case 3: // 黃
    LED(255,255,0);
    break;  
  case 4: // 綠
    LED(0,255,0);
    break;
  case 5: // 藍
    LED(0,0,255);
    break;  
  case 6: // 紫
    LED(139,0,255);
    break;  
  default:
    // if nothing else matches, do the default
    // default is optional
    break;
}
/*  
  Serial.print("ADC值 = ");
  Serial.println(val);
  Serial.print("電壓值 = ");
  Serial.println(val/1023.0 * 5);
*/  
  delay(200);
}

void LED(int r, int g, int b){
  analogWrite(redPin,r);
  analogWrite(greenPin,g);
  analogWrite(bluePin,b);
}
