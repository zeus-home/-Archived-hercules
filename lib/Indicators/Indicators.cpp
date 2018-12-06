#include "Indicators.h"
#include <Arduino.h>

unsigned long Indicators::previousMillis = 0;
int Indicators::ledState = LOW;

void Indicators::init() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void Indicators::blink_symmetric(uint8_t led, uint16_t period) {

    int delay = period / 2;
    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis >= delay) {
        previousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(led, ledState);
    }
}
