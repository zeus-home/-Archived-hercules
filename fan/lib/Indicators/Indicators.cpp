#include "Indicators.h"

#include <Arduino.h>

void Indicators::blink_symmetric(int led, int duration) {
    digitalWrite(led, LOW);
    delay(duration);
    digitalWrite(led, HIGH);
    delay(duration);
}