// 定義光敏電阻的腳位
const int photoPin_L = A0;  // 左光敏電阻 腳位
const int photoPin_M = A1;  // 中光敏電阻 腳位
const int photoPin_R = A2;  // 右光敏電阻 腳位

int valM, valL, valR;  // 記錄中/左/右光感值

void setup() {
  Serial.begin(9600);
}

void loop() {
  readPhoto();
  Serial.println(String("L=") + valL + ", M=" + valM + ", R=" + valR);
  delay(300);
}

// 讀取 20 次光感值取平均
void readPhoto() {
  valM = valL = valR = 0;

  //讀取 20 次感測值, 然後加總後放入變數
  for (int i = 0; i < 20; i++) {
    valM += analogRead(photoPin_M);
    valL += analogRead(photoPin_L);
    valR += analogRead(photoPin_R);
  }

  // 除以 20 取平均
  valM /= 20;
  valL /= 20;
  valR /= 20;
}

