#include <Arduino.h>
#include "MAIN.h"

MAINmodule MAIN(24,0x76,80);

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(137, 193, 91, 147);

void setup() {
  delay(3000);

  Serial.begin(9600);
  Serial.println(1);
  MAIN.config(0);
  Serial.println(2);
  MAIN.LANsetup(mac,ip);
  Serial.println(3);
}

void loop() {
  if(MAIN.clientConnected())
  {
    Serial.println("connected! \n Hello");
    MAIN.printDataLAN("Hello");
  }
}
  ..