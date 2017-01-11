
/*
   Defaults
*/

#define SETUPPIN 2
#define DEFAULT_SSID "Zabbiot"
#define DEFAULT_SECRET "zabbIoT"
#define DEFAULT_PROV_URL "http://zabbiot.local/%s.json"
#define EEPROM_SIZE 1024
#define CONFIG_START 0
#define CONFIG_VERSION "zoT"

#define ZABBIX_TIMEOUT 1000

/*
   Debug variables
*/
// To go always to factory reset mode (mostly testing)
#define DBG_FORCE_SETUP
// To enable debuging to serial (longer code)
//#define DBG_SERIAL

/*
    Define serial as output for messages
*/
#ifdef DBG_SERIAL
#define OPENLOG
#define PRINT(...) Serial.print(__VA_ARGS__)
#define PRINTln(...) Serial.println(__VA_ARGS__)
#define PRINTf(...) Serial.printf(__VA_ARGS__);
#define CLOSELOG
#else
#define OPENLOG
#define PRINT(...)
#define PRINTln(...)
#define PRINTf(...)
#define CLOSELOG
#endif

/*
   Sleep function
*/
//#define SLEEP(s) for (word si=1;si<s;si++) delay(1000)  // Standard delay
#define SLEEP(s) ESP.deepSleep(s * 1000 * 1000); // Optimized for low power on ESP


