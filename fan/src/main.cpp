#include <Arduino.h>
#include <EEPROM.h>
#include <Hercules.h>
#include <HerculesParams.h>
#include <HerculesWireless.h>
#include <HttpServer.h>
#include <Indicators.h>
#include <MqttServer.h>


int reset = D1;
bool resetUnpressed = true;
unsigned long startTime;
unsigned long pressTime;

HerculesWireless wireless;
HttpServer *http_server;
MqttServer *mqtt_server;

bool isConfigured;

#define AP_SSID "[Hercules]2934FCD34"
#define AP_PASS "IrisConfig"

void checkForResetButton();

void setup() {
  Serial.begin(9600);
  isConfigured = HerculesParams::isConfigured();
  if(!isConfigured) {
    wireless.initializeAP();
    http_server = new HttpServer();
    http_server->begin();
  } else {
    wireless.initializeSTA();
    mqtt_server = new MqttServer();
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

  checkForResetButton();

  if(!isConfigured) {
    http_server->handleClient();
  } else {
    mqtt_server->handleClient();
    Indicators::blink_symmetric(LED_BUILTIN, 1000);
  }
}

void checkForResetButton() {
  if(digitalRead(reset) == HIGH) {
    if(resetUnpressed) {
      startTime = millis();
      resetUnpressed = false;
    }
    pressTime = millis()-startTime;
    mqtt_server->sendMessage("Pressed");
    if(pressTime > 10000) {
      Hercules::restart();
    } else {
      return;
    }
  } else {
    resetUnpressed = true;
  }
}
