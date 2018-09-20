#include <Arduino.h>
#include <EEPROM.h>
#include <Hercules.h>
#include <HerculesDriver.h>
#include <HerculesParams.h>
#include <HerculesWireless.h>
#include <HttpServer.h>
#include <Indicators.h>
#include <MqttServer.h>

#define ZERO_CROSSING D2
#define RESET D1

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

struct HerculesIdentifier {
  uint32_t chipId;

  String toJSON() {
    String x = String("{\"chipId\": \"");
    String z = String(chipId);
    String y = String("\"}");
    return x+z+y;
  }

} HerculesId;


void setup() {
  Serial.begin(9600);
  HerculesId.chipId = ESP.getChipId();
  Indicators::init();
  digitalWrite(LED_BUILTIN, LOW);
  isConfigured = HerculesParams::isConfigured();
  if(!isConfigured) {
    wireless.initializeAP();
    http_server = new HttpServer();
    http_server->begin();
    Serial.println("\nConfiguration Mode\n");
  } else {
    wireless.initializeSTA();
    mqtt_server = new MqttServer();
    mqtt_server->connect();
    mqtt_server->initialize();
    mqtt_server->sendMessage(HerculesId.toJSON());
    Serial.println("\nOperation Mode\n");
    attachInterrupt(digitalPinToInterrupt(ZERO_CROSSING), HerculesDriver::interrupt, RISING);
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
    HerculesDriver::handleDevices();
    Indicators::blink_symmetric(LED_BUILTIN, 1000);
  }
}

void checkForResetButton() {
  if(digitalRead(RESET) == HIGH) {
    if(resetUnpressed) {
      startTime = millis();
      resetUnpressed = false;
    }
    pressTime = millis() - startTime;
    mqtt_server->sendMessage(String("Pressed"));
    if(pressTime > 10000) {
      Hercules::restart();
    }
  } else {
    resetUnpressed = true;
  }
}
