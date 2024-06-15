/*
 * 藍牙RGB LED範例                     © 華夏科大電子系 吳宗憲
 * 搭配藍牙手機APP來控制(SoundControlRGB.aia)
 * 本範例支援呼吸燈及彩虹燈
 */
// 藍牙的TX腳位請連結------Arduino 的D2腳位
// 藍牙的RX腳位請連結------Arduino 的D3腳位
#include <SoftwareSerial.h>

#define Rxpin     2
#define Txpin     3
#define bluePin   9
#define greenPin 10
#define redPin   11

SoftwareSerial BT = SoftwareSerial(Rxpin,Txpin);
int btIn[4];

void setup() {
  randomSeed(analogRead(0));          // 亂數種子
  
  //Serial.begin(9600);
  BT.begin(9600);
}

void loop() {
  int i;
  
  getBTIn(btIn);                   // 接收藍牙指令
  
  switch (btIn[0]){
    case 1:                        // 單色開關燈
      showColor(btIn[1], btIn[2], btIn[3]);
    break;
    case 2:                        // 單色呼吸燈
      chooseColor(btIn[1], btIn[2], btIn[3]);
    break;
    case 3:                        // 彩色呼吸燈
      for (i = 1; i <= 255; i++) {
        btIn[1] = random(1,i);
        btIn[2] = random(1,i);
        btIn[3] = random(1,i);
        breathing(btIn[1], btIn[2], btIn[3]);
        delay(10);
      }
      for (i = 255; i >= 0; i--) {
        btIn[1] = random(1,i);
        btIn[2] = random(1,i);
        btIn[3] = random(1,i);
        breathing(btIn[1], btIn[2], btIn[3]);
        delay(10);
      }
    break;
    case 4:                        // 彩虹燈  
      rainbow(20);
    break;
    default:
    break;  
  }     
  delay(20);
}

// 呼吸燈特效
void breathing(int r, int g, int b) {
  float bright = (exp(sin(millis() / 2000.0 * PI)) - 0.36787944) * 108.0;  // 代入呼吸燈公式
  bright = bright / 255;          // 先除 255, 下一行再乘以指定的 3 原色值
  showColor(bright * r, bright * g, bright * b);
}

// 彩虹特效
void rainbow(int wait) {
  for (int i = 0; i < 256; i++) {
     Wheel( i );
     delay(wait);
  }
}

// 色輪函式：產生漸變顏色值的函式
void Wheel(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    showColor (255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else if (WheelPos < 170) {
    WheelPos -= 85;
    showColor (0, WheelPos * 3, 255 - WheelPos * 3);
  }
 else {
   WheelPos -= 170;
   showColor (WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}

void showColor(int r, int g, int b) {
  analogWrite (redPin, r);  
  analogWrite (greenPin, g); 
  analogWrite (bluePin, b);
}
// 選(單)色呼吸燈
void chooseColor(int r, int g, int b){
  int i;
  
  for(i = 1; i <= 255; i++){
    if (r && g && b)
      breathing(i, i, i);
    else if (r)
      breathing(i, 0, 0);
    else if (g)
      breathing(0, i, 0);
    else
      breathing(0, 0, i);
    delay(10);
  }
  for(i = 255; i >= 0; i--){
    if (r && g && b)
      breathing(i, i, i);
    else if (r)
      breathing(i, 0, 0);
    else if (g)
      breathing(0, i, 0);
    else
      breathing(0, 0, i);
    delay(10);
  }
}

// 接收藍牙傳輸的資料，並分別存入 btIn[]
void getBTIn(int *btIn) {
  int b[3] = {0,0,0};       // b[]+1為","的位置
  String target = ",";      // 搜尋的字元  
  int i = 0, pos = 0, count = 0;
  String s = "";
  String s0 = "";   // d1，何種操作？加減油門(1)或左右轉向(2)或迴旋、九宮格微調(3)
  String s1 = "";   // d2
  String s2 = "";   // d3
  String s3 = "";   // d4

  while (BT.available())
    s = BT.readString();
    
  if (s != "") {    
    while ((i = s.indexOf(target,pos)) != -1) {
      b[count] = i+1;
      //Serial.println(b[count]);
      count++;
      pos = i+1;
    }  
    s0 = s.substring(0,b[0]-1);
    s1 = s.substring(b[0],b[1]-1);
    s2 = s.substring(b[1],b[2]-1);
    s3 = s.substring(b[2],s.length());
    btIn[0] = s0.toInt();
    btIn[1] = s1.toInt();
    btIn[2] = s2.toInt();
    btIn[3] = s3.toInt();
  }
}

