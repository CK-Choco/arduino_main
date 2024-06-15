/*從序列埠控制 LED 開關
 * 1: on ; 0: off ; 2: run
 */
char val;         // 儲存接收資料的變數，採字元類型
const byte LEDs[] = {8,9,10};
const byte total = sizeof(LEDs);
boolean toggle = false;    // 輸出給 LED 的訊號，預設為「低電位」
int index = 0;

void setup() {
  Serial.begin(9600);
  for (byte i=0; i<total; i++) {
    pinMode(LEDs[i], OUTPUT);
  }
  Serial.println("1: on ; 0: off!; 2 : run!");
}

void loop() {
  if( Serial.available() ) {
    val = Serial.read();
    switch (val) {
    case '0':
      for (byte i=0; i<total; i++) {
        digitalWrite(LEDs[i], LOW);
      }
      toggle = false;
      Serial.print("LED OFF\n");
    break;
    case '1':
      for (byte i=0; i<total; i++) {
        digitalWrite(LEDs[i], HIGH);
      }
      toggle = false;
      Serial.println("LED ON");
    break;
    case '2':
      toggle = true;
      Serial.println("跑馬燈!");
    break;
    default:
      Serial.println("別亂按!");
    }
  }   
  if (toggle){            // 跑馬燈
    for (byte i=0; i<total; i++) {
      digitalWrite(LEDs[i], LOW);
    }    
    digitalWrite(LEDs[index], HIGH);
    index ++;
    if (index == total) {
      index = 0;
    }
    delay(400);
  }
  
}
