#include "HerculesWireless.h"
#include <Arduino.h>
#include <Credentials.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>

HerculesWireless::HerculesWireless() {
    apIP = new IPAddress(192, 168, 24, 5);
}

void HerculesWireless::initializeAP() {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(*apIP, *apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(AP_SSID, AP_PSK);
}

void HerculesWireless::initializeSTA() {
    Credentials cred = getCredentials();
    WiFi.mode(WIFI_STA);
    WiFi.begin(cred.ssid, cred.psk);
    Serial.println("Connecting");
    while(!WiFi.isConnected()) {
        Serial.print(".");
        delay(100);
    }
    Serial.println("\nConnected to WiFi Network");
}

void HerculesWireless::putCredentials(Credentials cred) {
    EEPROM.begin(512);
    EEPROM.put(0 + sizeof(bool), cred);
    char ok[2 + 1] = "OK";
    EEPROM.put(0 + sizeof(bool) + sizeof(cred), ok);
    EEPROM.commit();
    EEPROM.end();
}

Credentials HerculesWireless::getCredentials() {
    EEPROM.begin(512);
    EEPROM.get(0 + sizeof(bool), STA_CRED);
    char ok[2 + 1];
    EEPROM.get(0 + sizeof(bool) + sizeof(STA_CRED), ok);
    EEPROM.end();
    return this->STA_CRED;
}
