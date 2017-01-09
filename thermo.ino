

char *OWdevToStr(const uint8_t* dev)
{
  char result[20];
  sprintf(result, "%x%x%x%x%x%x%x%x", dev[0], dev[1], dev[2], dev[3], dev[4], dev[5], dev[6], dev[7]);
  return result;
}

// Setup thermo sensors and bus
bool thermoSetup() {
  ds.reset();
}

// Get next device (repeat to get all)
// Return address of 0 on end
bool thermoNextDevice() {
  if (!ds.search(Thermo_device)) {
    PRINTln("OW: No more addresses.");
    ds.reset();
    delay(250);
    return (false);
  } else {
    PRINTf("OW: found device %s\n", OWdevToStr(Thermo_device));
    return (true);
  }
}

// Read temperature from sensor with given address
bool thermoRead() {
  byte data[12];
  int i;
  int present;

  if ( OneWire::crc8( Thermo_device, 7) != Thermo_device[7]) {
    PRINTln("CRC is not valid!");
    return (false);
  }

  if ( Thermo_device[0] != 0x10) {
    PRINTln("Device is not a DS18S20 family device.");
    return (false);
  }

  ds.reset();
  ds.select(Thermo_device);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  delay(1000);     // maybe 750ms is enough, maybe not
  present = ds.reset();
  ds.select(Thermo_device);
  ds.write(0xBE);         // Read Scratchpad

  PRINT("P=");
  PRINT(present, HEX);
  PRINT(" ");
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
    PRINT(data[i], HEX);
    PRINT(" ");
  }
  PRINT(" CRC=");
  PRINT( OneWire::crc8( data, 8), HEX);
  PRINTln();
}

bool thermoStop() {
  // Probably nothing. Maybe turn wire off
}

