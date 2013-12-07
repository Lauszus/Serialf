#include <Serialf.h>

Serialf serialf(&Serial);
Serialf serialf1(&Serial1);

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  serialf.printf("HelloWorld1\r\n");
  serialf1.printf("HelloWorld2\r\n");
  delay(1000);
}
