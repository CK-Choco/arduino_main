/*
 * RGB LED 亂數產生RGB顏色
 * 本範例主要先讓同學認識RGB LED接線電路及設定顏色的方法
 */
#define bluePin   9
#define greenPin 10
#define redPin   11

void setup() {
  randomSeed(analogRead(0));          // 亂數種子
}

void loop() {
    int blueValue;
    int redValue;
    int greenValue;
    
    for(redValue = 1; redValue <= 255; redValue++){
        analogWrite(redPin, redValue);
        delay(10);
    }
    for(redValue = 255; redValue >= 0; redValue--){
        analogWrite(redPin, redValue);
        delay(10);
    }
    for(greenValue = 1; greenValue <= 255; greenValue++){
        analogWrite(greenPin, greenValue);
        delay(10);
    }
    for(greenValue = 255; greenValue >= 0; greenValue--){
        analogWrite(greenPin, greenValue);
        delay(10);
    }
    for(blueValue = 1; blueValue <= 255; blueValue++) {
        analogWrite(bluePin, blueValue);
        delay(10);
    }
    for(blueValue = 255; blueValue >= 0; blueValue--) {
        analogWrite(bluePin, blueValue);
        delay(10);
    }
    for (int i = 1; i <= 125; i++) {
        redValue=random(1,i);
        greenValue=random(1,i);
        blueValue=random(1,i);
        analogWrite(redPin,redValue);
        analogWrite(greenPin,greenValue);
        analogWrite(bluePin,blueValue);
        delay(500);
    }
    analogWrite(redPin,0);
    analogWrite(greenPin,0);
    analogWrite(bluePin,0);
}

