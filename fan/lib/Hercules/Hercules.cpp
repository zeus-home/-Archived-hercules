#include "Hercules.h"

#include <Arduino.h>
#include <HerculesParams.h>

void Hercules::restart() {
    Serial.println("Resetting...");
    HerculesParams::setConfigured(false);
    delay(2000);
    ESP.restart();
}