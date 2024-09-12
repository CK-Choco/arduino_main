#define _baud       9600
#define FanPin      8

void setup() {
  pinMode(FanPin,OUTPUT);
  Serial.begin(_baud);
}

void loop() {
  char c;
  
  if (Serial.available()){
    c = Serial.read();
    if ( c == '0')
      digitalWrite(FanPin,LOW);
    else
      digitalWrite(FanPin,HIGH);    
  }
}
