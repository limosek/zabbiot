
StaticJsonBuffer<200> zJsonBuff;
JsonObject& zJson = zJsonBuff.createObject();

StaticJsonBuffer<200> zJsonDataBuff;
JsonArray& zData = zJsonDataBuff.createArray();

bool zabbixSetup();

bool addZabbixItem(char *k, float value);

bool sendZabbix();

bool zabbixLoopStart();

bool zabbixLoopEnd();

