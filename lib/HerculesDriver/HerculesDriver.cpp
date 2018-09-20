#include "HerculesDriver.h"

#include <Arduino.h>

unsigned long HerculesDriver::zeroTime = 0;
int HerculesDriver::ledState = LOW;

bool HerculesDriver::deviceState[] = { false, false, false };

void HerculesDriver::interrupt() {
    zeroTime = millis();
    if(ledState == LOW) {
        ledState = HIGH;
    } else {
        ledState = LOW;
    }
    digitalWrite(D3, ledState);
}

void HerculesDriver::handleDevices() {
    unsigned long timeElapsed = millis() - zeroTime;
    double angle = (timeElapsed * 180) / HALF_CYCLE_INTERVAL;
    
}
