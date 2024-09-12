void setup() {
  Serial.begin(9600);
  
}

void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);
  int z=0;
  z=x-y;
  Serial.println(z);

  delay(500);
}