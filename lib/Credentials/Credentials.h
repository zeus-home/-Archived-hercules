#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <Arduino.h>

struct Credentials {
    char ssid[25];
    char psk[25];

    String toJSON() {
        String s_ssid = String(ssid);
        String s_psk = String(psk);
        return String("{\"ssid\": \"" + s_ssid + "\", \"psk\": \"" + s_psk + "\"}");
    }

};

#endif