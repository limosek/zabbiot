
bool shouldSetup() {
#ifdef DBG_FORCE_SETUP
  return (true);
#else
  if (!loadConfig()) {
    return (true);
  } else {
    // Some other way to factory defaults
  }
#endif
}

char *macToStr(const uint8_t* mac)
{
  char result[20];
  sprintf(result, "%x:%x:%x:%x:%x:%x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return result;
}

void provDefaults() {
  int i;
  String configdata;
  char url[200];
  uint8_t mac[] = {0, 0, 0, 0, 0, 0};

  PRINT("Entering factory defaults mode...");
  WiFi.begin(DEFAULT_SSID, DEFAULT_SECRET);
  PRINT("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    PRINT(".");
  }
  PRINTln();
  for (i = 0 ; i < sizeof(Config) ; i++) {
    EEPROM.write(CONFIG_START + i, 0);
  }
  sprintf(url, DEFAULT_PROV_URL, macToStr(WiFi.macAddress(mac)));
  configdata = fetchUrl(url);
  parseConfig(configdata);
  dumpConfig();
  Reset();
}

