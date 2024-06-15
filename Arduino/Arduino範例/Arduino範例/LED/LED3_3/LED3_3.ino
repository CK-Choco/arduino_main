// 跑馬燈範例程式三

const byte LEDs[] = {8,9,10};
const byte total = sizeof(LEDs);
byte index = 0;

void setup() {
  for (byte i=0; i<total; i++) {
    pinMode(LEDs[i], OUTPUT);
  }
}

void loop() {
  for (byte i=0; i<total; i++) {
    digitalWrite(LEDs[i], LOW);
  }
  
  digitalWrite(LEDs[index], HIGH);
  index ++;
  if (index == total) {
    index = 0;
  }
  delay(200);
}


