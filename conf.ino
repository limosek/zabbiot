
bool loadConfig() {
  if (EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
      EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
      EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2]) {
    for (unsigned int t = 0; t < sizeof(Config); t++) {
      *((char*)&Config + t) = EEPROM.read(CONFIG_START + t);
    }
    return (true);
  } else {
    return (false);
  }
}

void saveConfig() {
  for (unsigned int t = 0; t < sizeof(Config); t++)
    EEPROM.write(CONFIG_START + t, *((char*)&Config + t));
}

void resetConfig() {
  EEPROM.write(CONFIG_START, 0);
}

void parseConfig(String cfg) {
  char tmp[64];

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(cfg);
  // If reset triggered from remote config
  strcpy(tmp, root["reset"]);
  if (strcmp(tmp, "1")) {
    resetConfig();
    Reset;
  }
  strncpy(Config.ssid, root["ssid"], 64);
  strncpy(Config.secret, root["secret"], 64);
  strcpy(tmp, root["ip"]);
  if (strcmp(tmp, "dhcp")) {
    Config.dhcp = true;
  } else {
    Config.dhcp = false;
    if (!Config.ip.fromString(tmp)) {
      PRINTln("Bad IP address");
      Reset();
    }
    strcpy(tmp, root["gw"]);
    if (!Config.gw.fromString(tmp)) {
      PRINTln("Bad GW address");
    }
    strcpy(tmp, root["dns"]);
    if (!Config.dns.fromString(tmp)) {
      PRINTln("Bad DNS address");
    }
    strcpy(tmp, root["prefix"]);
    Config.prefix = atoi(tmp);
    strcpy(tmp, root["interval"]);
    Config.interval = atoi(tmp);
    strcpy(tmp, root["onewire_pin"]);
    Config.onewire_pin = atoi(tmp);
  }
}

void dumpConfig() {
  PRINT("Mode: ");
  PRINT("SSID: ");
  PRINTln(Config.ssid);
  PRINT("Secret: ");
  PRINTln(Config.secret);
  if (!Config.dhcp) {
    PRINT("IP: ");
    PRINT(Config.ip);
    PRINT("/");
    PRINTln(Config.prefix);
    PRINT("GW: ");
    PRINTln(Config.gw);
    PRINT("DNS: ");
    PRINTln(Config.dns);
  } else {
    PRINTln("IP: DHCP");
  }
}

