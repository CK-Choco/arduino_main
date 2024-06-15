int sunshine_East=0,sunshine_West=0;//日照東,日照西
void setup() {
  Serial.begin(9600);
}
void loop() {
  sunshine_East = analogRead(A0);   //A0為日照東
  sunshine_West = analogRead(A1);   //A1為日照西

  Serial.print("\nEast=");
  Serial.print(1024-sunshine_East);

  Serial.print("\nWest=");
  Serial.print(1024-sunshine_West);

  Serial.print("\n誤差=");
  Serial.print(sunshine_West-sunshine_East);

  if(sunshine_West-sunshine_East>=100 && sunshine_West-sunshine_East<=250){
    Serial.print("\n向西轉11.37度");
  }
  else if(sunshine_West-sunshine_East<100 && sunshine_West-sunshine_East>=-50){
    Serial.print("\n校正回歸完成");
  }
  else if(sunshine_West-sunshine_East<-50){
    Serial.print("\n向東轉11.37度");
  }  
  else if(sunshine_West-sunshine_East>250){
    Serial.print("\n誤差異常過大");
  }
    else if(sunshine_West-sunshine_East>1024 && sunshine_West-sunshine_East<-1024){
    Serial.print("\n異常故障數據");
  }
  Serial.print("\n");
  delay(1500);
}
