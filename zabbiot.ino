
/*
   Zabbiot project
*/

#include <EEPROM.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <dummy.h>
#include <ArduinoJson.h>
#include <OneWire.h>

#include "defines.h"
#include "prov.h"
#include "conf.h"
#include "thermo.h"

// Reset function
void (*Reset)(void) = 0;

void setup() {
  Serial.begin(115200);
  if (shouldSetup()) {
    provDefaults();
    delay(1000);
    Reset();
  } else {

  }
}

void loop() {
  thermoSetup();
  while (thermoNextDevice()) {
    thermoRead();
    PRINTf("Got value %f from device %s\n", Thermo_value, devToStr(Thermo_device));
  }
  thermoStop();
}


