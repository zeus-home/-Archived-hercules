#include "Indicators.h"

#include <Arduino.h>

unsigned long Indicators::previousMillis = 0;
int Indicators::ledState = LOW;

void Indicators::init() {
    pinMode(LED_BUILTIN, OUTPUT);
}

void Indicators::blink_symmetric(int led, int duration) {

    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        if(ledState == HIGH) {
            ledState = LOW;          
        } else {
            ledState = HIGH;
        }
        digitalWrite(LED_BUILTIN, ledState);

    }

    // digitalWrite(led, LOW);
    // delay(duration);
    // digitalWrite(led, HIGH);
    // delay(duration);
}
