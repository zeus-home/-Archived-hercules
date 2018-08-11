#include "HerculesParams.h"
#include <EEPROM.h>

bool HerculesParams::isConfigured() {
    bool isConfigured;
    EEPROM.begin(512);
    EEPROM.get(0, isConfigured);
    EEPROM.end();
    return isConfigured;
}

void HerculesParams::setConfigured(bool state) {
    EEPROM.begin(512);
    EEPROM.put(0, state);
    EEPROM.end();
}
