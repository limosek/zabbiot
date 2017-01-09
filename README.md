# Zabbiot
Zabbix IoT firmware for ESP8266 and similar systems.
Primary goal of this firmware is autoconfig and autodiscovery of thsi devices in Zabbix.
So everything you need is to upload firmware, fetch defaults over HTTP and use!
Firmware is used primarily for ESP8266 boards but it should not be problem to port.

## Dependencies
It needs arduinoJson package.

## Features
  * Only for ESP8266 now (should not be problem to extend)
  * Zabbix sender inside
  * Network config (provision) of devices
  * Autodiscovery of devices
  * Autodiscovery of sensors (at this time onewire thermometers)
  * No need to update firmware if Zabbix or network topology changes

## Why?
There is possibility to create firmware using "embeded" constants like server, IP, SSID etc. But it does not scale.
I wanted to create universal firmware which is able to autoconfigure using network provision.


## How it works?
Stock firmware in factory defaults mode will search for special SSID, next to this it will fetch its config from HTTP and save it to EEPROM.

 * Boot
 * If in factory reset
   * Connect to SSID 'Zabbiot' , secret 'zabbIoT'
   * Fetch http://zabbiot.local/{board_id}.json or http://192.168.167.1/{mac}.json 
   * Save data into EEPROM
   * Reboot

 * If not in factory reset
   * Connect to saved SSID with saved credentials
   * Connect to saved Zabbix server and autoregister device
   * Connect to saved Zabbix server and periodicaly send data from all sensors (via zabbix_sender)

## Config file format
Config file is standard json file. Please note that it has to be well and exactly formated.
```
{
  "ssid": "test",
  "secret": "trest",
  "ip": "1.2.3.4",
  "prefix": 24
  "zabbix_host": "1.2.3.5",
  "zabbix_port": "10051",
  "interval": "600"
}

```

