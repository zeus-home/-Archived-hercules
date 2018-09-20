#include <Credentials.h>
#include <ESP8266WiFi.h>

#ifndef HERCULES_WIRELESS_H
#define HERCULES_WIRELESS_H

class HerculesWireless {
  private: 
    Credentials STA_CRED;
    IPAddress* apIP;
    const char* AP_SSID = "[Hercules]2934FCD34";
    const char* AP_PSK = "IrisConfig";

  public:
    HerculesWireless();
  
    void initializeAP();

    void initializeSTA();

    void putCredentials(Credentials cred);

    Credentials getCredentials();

};

#endif
