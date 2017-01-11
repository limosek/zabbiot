
bool initZabbix() {
  StaticJsonBuffer<50> tmp;
  zJson["request"] = "sender data";
  zJson["data"] = tmp.createArray();
}

bool addZabbixItem(char *k, char *value) {
  StaticJsonBuffer<100> itemBuff;
  JsonObject& item = itemBuff.createObject();

  item["host"] = Config.hostname;
  item["key"] = k;
  item["value"] = value;
  zData.add(item);
}

bool sendZabbix() {
  char packet[512];
  int length;
  
  zJson.printTo(packet);
  if (zClient.connect(Config.zabbix_server, Config.zabbix_port)) {
    length = zJson.measureLength();
    zJson.printTo(packet,length);
    zClient.write((char *) packet, length);
    for (int i = 0; i < ZABBIX_TIMEOUT / 10; i++) {
      if (zClient.available()) {
        return(1);
      }
      delay(10);
    }
  } else {
    return(0);
  }
}


bool zabbixLoopStart() {
  
}

bool zabbixLoopEnd() {
  
}


