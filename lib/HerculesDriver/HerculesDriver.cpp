#include "HerculesDriver.h"

#include <Arduino.h>

unsigned long HerculesDriver::zeroTime = 0;

bool HerculesDriver::deviceState[] = { false, false, false };

void HerculesDriver::interrupt() {
    zeroTime = millis();
}

void HerculesDriver::handleDevices() {
    unsigned long timeElapsed = millis() - zeroTime;
    double angle = (timeElapsed * 180) / HALF_CYCLE_INTERVAL;
    
}
