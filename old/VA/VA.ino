#include <Wire.h>
#include "ACS712.h"
int val11;
float val2;

ACS712  ACS(A0, 5.0, 1023, 100);

void setup()
{
  Serial.begin(9600);
  ACS.autoMidPoint();
}

void loop()
{
    //電壓
      float temp;
      val11=analogRead(A1);
      temp=val11/4.092;
      val2=(temp/10);
      Serial.println("V:");
      Serial.println(val2);
    //電流
      float mA = ACS.mA_DC(),A=0;
      A=(mA/1000/5000)*(val2*100);
      Serial.println("A:");
      Serial.println(A);
   delay(500);
}