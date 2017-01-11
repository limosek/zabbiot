
/*
   Config structure. Global variable
*/

struct EEPROM_CONFIG {
  bool reset;
  int onewire_pin;
  word interval;
  char version[4];
  char ssid[64];
  char secret[64];
  byte prefix;
  bool dhcp;
  IPAddress zabbix_server;
  word zabbix_port;
  char hostname[32];
  IPAddress ip;
  IPAddress gw;
  IPAddress dns;
  char http_uri[64];
} Config;

bool loadConfig();

void saveConfig();

void parseConfig(String cfg);

void dumpConfig(String cfg);
