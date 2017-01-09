
byte Thermo_device[8];
float Thermo_value;
OneWire ds(Config.onewire_pin);

char *OWdevToStr(const uint8_t* dev);

bool thermoSetup();

bool thermoNextDevice();

bool thermoRead();

bool thermoStop();

