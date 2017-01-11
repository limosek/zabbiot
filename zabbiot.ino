
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
#include "zabbix.h"
#include "http.h"

WiFiClient zClient;

// Reset function
void (*Reset)(void) = 0;

void setup() {
  Serial.begin(115200);
  if (shouldSetup()) {
    provDefaults();
    delay(1000);
    Reset();
  } else {
    thermoSetup();
    zabbixSetup();
    httpSetup();
  }
}

void loop() {
  PRINTln("Global loop start");
  httpLoopStart();
  zabbixLoopStart();
  thermoLoopStart();
  
  thermoLoopEnd();
  zabbixLoopEnd();
  httpLoopEnd();
  PRINTf("Global loop end, sleeping %d seconds.\n",Config.interval);
  SLEEP(Config.interval);
}


