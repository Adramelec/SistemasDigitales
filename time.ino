#include <DS1302.h>

 const int RST   = 7;  // Chip Enable
 const int DAT   = 8;  // Input/Output
 const int CLK = 2;  // Serial Clock

DS1302 rtc(RST, DAT, CLK);

void printTime() {
  Time t = rtc.time();
  int a = t.yr; 
  int m = t.mon;
  int d = t.date;
  int h = t.hr;
  int M = t.min;

Serial.print(a);
  Serial.print(',');
  Serial.print(m);
  Serial.print(',');
  Serial.print(d);
  Serial.print(',');
  Serial.print(h);
  Serial.print(',');
  Serial.print(M);
}

void setup() {
  Serial.begin(9600);

  rtc.writeProtect(false);
  rtc.halt(false);

  Time t(2020, 11, 23, 5, 55, 50, Time::kMonday);

  rtc.time(t);
}

void loop() {
  printTime();
  delay(1000);
}
