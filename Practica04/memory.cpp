#include <EEPROM.h>
void getEeprom(int address, int &value){
  EEPROM.get(address,value);
}
void putEeprom(int address, int value){
  EEPROM.put(address,value);
}
