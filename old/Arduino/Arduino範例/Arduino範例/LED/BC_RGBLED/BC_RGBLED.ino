/*
 * 本範例實作呼吸燈及彩虹燈                 © 華夏科大電子系 吳宗憲
 * 循序產生紅、綠、藍、亂數產生的呼吸燈及彩虹燈
 */
#define bluePin   9
#define greenPin 10
#define redPin   11

void setup() {
  randomSeed(analogRead(0));          // 亂數種子
}

void loop() {    
  int redValue;
  int greenValue;
  int blueValue;
    
  for(redValue = 1; redValue <= 255; redValue++){
    breathing(redValue, 0, 0);
    delay(10);
  }
  for(redValue = 255; redValue >= 0; redValue--){
    breathing(redValue, 0, 0);
    delay(10);
  }
  for(greenValue = 1; greenValue <= 255; greenValue++){
    breathing(0, greenValue, 0);
    delay(10);
  }
  for(greenValue = 255; greenValue >= 0; greenValue--){
    breathing(0, greenValue, 0);
    delay(10);
  }
  for(blueValue = 1; blueValue <= 255; blueValue++) {
    breathing(0, 0, blueValue);
    delay(10);
  }
  for(blueValue = 255; blueValue >= 0; blueValue--) {
    breathing(0, 0, blueValue);
    delay(10);
  }
  for (int i = 1; i <= 255; i++) {
    redValue = random(1,i);
    greenValue = random(1,i);
    blueValue = random(1,i);
    breathing(redValue, greenValue, blueValue);
    delay(40);
  }
  showColor(0,0,0);
  delay(1000);

  for (int i = 1; i <= 10; i++)
    rainbow(20);  
}

// 曲線型變化的呼吸燈特效
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


