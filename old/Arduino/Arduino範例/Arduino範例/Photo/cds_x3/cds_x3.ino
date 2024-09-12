// 定義光敏電阻的腳位
const int photoPin_L = A0; // 左光敏電阻 腳位
const int photoPin_M = A1; // 中光敏電阻 腳位
const int photoPin_R = A2; // 右光敏電阻 腳位

int valL, valM, valR;  // 記錄左/中/右光感值

void setup() {
  Serial.begin(9600);
}

void loop() {
  // 讀取左/中/右光感值
  valL = analogRead(photoPin_L);
  valM = analogRead(photoPin_M);
  valR = analogRead(photoPin_R);

  // 將左/中/右光感值透過 Serial 輸出到電腦
  Serial.println(String("L=") + valL + ", M=" + valM + ", R=" + valR);

  delay(1000);
}

