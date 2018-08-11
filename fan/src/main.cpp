#include <EEPROM.h>
#include <HttpServer.h>
#include <HerculesParams.h>
#include <HerculesWireless.h>
#include <ESP8266WiFi.h>

HttpServer *http_server;
HerculesWireless wireless;
bool isConfigured;

#define AP_SSID "[Hercules]2934FCD34"
#define AP_PASS "IrisConfig"

void setup() {
  Serial.begin(9600);
  // HerculesParams::setConfigured(false);
  isConfigured = HerculesParams::isConfigured();
  if(!isConfigured) {
    wireless.initializeAP();
    http_server = new HttpServer();
    http_server->begin();
  } else {
    wireless.initializeSTA();
  }
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  if(isConfigured) {
      Serial.println("\nOperation Mode");
  } else {
      Serial.println("\nConfiguration Mode");
  }
  Credentials cred = wireless.getCredentials();
  Serial.println(cred.toJSON());
}

void loop() {
  if(!isConfigured) {
    http_server->handleClient();
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
}

