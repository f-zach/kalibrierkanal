#include <Arduino.h>
#include "MAIN.h"
#include "PRS.h"

MAINmodule MAIN(24, 0x76, 80);
PRSmodule PRS(0x70);

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(137, 193, 91, 147);

float SensorRanges[8] = {100, 100, 100, 100, 0, 0, 0, 0};
int UnitSensors[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int UnitReq[8] = {0, 0, 0, 0, 0, 0, 0, 0};
byte pSens_i2c_address[8] = {0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48};

String DataString;

void setup()
{
  delay(3000);

  Serial.begin(9600);

  Wire.begin(I2C_MASTER,0x00,I2C_PINS_18_19);
  Serial.println(1);
  MAIN.config(0);
  MAIN.LANsetup(mac, ip);
  Serial.println(2);

  PRS.config(B00001111, SensorRanges, B00001111, UnitSensors, UnitReq, pSens_i2c_address);
  Serial.println(3);
}

void loop()
{
  if (MAIN.clientConnected())
  {
    PRS.readPressAll();

    for (int i = 0; i < PRS.SensorCount; i++)
    {
      DataString += String(PRS.Pressure[i]) + "\t";
    }
    DataString += "\n";

    MAIN.printDataLAN(DataString);
  }
}