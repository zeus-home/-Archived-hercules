#include <Arduino.h>

#ifndef INDICATORS_H
#define INDICATORS_H

// #define interval 1000 

class Indicators {

    static unsigned long previousMillis;
    static int ledState;

    public:
        static void init();
        
        static void blink_symmetric(uint8_t pin, uint16_t period);

};

#endif
