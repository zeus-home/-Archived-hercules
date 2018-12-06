#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

unsigned long zeroTime = 0;
int pulseWidth = 2;
int light_state = 0;
int fan_state = 0;

// WIFI SETTINGS
#define WIFI_SSID "OnePlus 6"
#define WIFI_PSK  "9821880713"

// MQTT SETTINGS
#define MQTT_SERVER "m15.cloudmqtt.com"
#define MQTT_PORT 13902
#define MQTT_USER "uglryohs"
#define MQTT_PASS "JKJlnLuvBN31"

#define TOPIC_LIGHT "hercules/sub/ESP_52F5B5/light"
#define TOPIC_FAN "hercules/sub/ESP_52F5B5/fan"
#define TOPIC_SWITCH "hercules/sub/ESP_52F5B5/switch"
#define TOPIC_PUB "message"

WiFiClient espClient;
PubSubClient client(espClient);

const int LED = D4;
const int Switch = D5;
const int Fan = D6;
const int Light = D7;

int fireDelay(int firingAngle) { 
  return (20*firingAngle)/360;
}

void toggle();
void onMessage(char* topic, byte* payload, unsigned int length);

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  pinMode(Light, OUTPUT);
  pinMode(Fan, OUTPUT);
  pinMode(Switch, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(D2), toggle, RISING);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  Serial.println("Connecting");
  while(!WiFi.isConnected()) {
      Serial.print(".");
      delay(100);
  }
  Serial.println("\nConnected to WiFi Network");

  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(onMessage);

  Serial.println("Attempting connection to Tesseract...");
  while(!client.connected()) {
      if(client.connect("ESP_52F5B5", MQTT_USER, MQTT_PASS)) {
          Serial.println("\nConnected!");
          client.subscribe(TOPIC_LIGHT);
          client.subscribe(TOPIC_FAN);
          client.subscribe(TOPIC_SWITCH);
          client.publish(TOPIC_PUB, "Connection established");
      } else {
          Serial.print(".");
          delay(1000);
      }
  }
  digitalWrite(LED, LOW);
  Serial.println("Connected");

}

int firingAngle_light = 0;
int firingAngle_fan = 0;
unsigned long currentTime;

void loop() {
  currentTime = millis();
  int firingDelay_light = fireDelay(firingAngle_light);
  if(currentTime - zeroTime < firingDelay_light) {
    light_state = LOW;
  } else if(currentTime - zeroTime >= firingDelay_light && currentTime - zeroTime < firingDelay_light + pulseWidth) {
    light_state = HIGH;
  } else if(currentTime - zeroTime >= firingDelay_light + pulseWidth) {
    light_state = LOW;
  }
  // Serial.println(x);
  currentTime = millis();
  int firingDelay_fan = fireDelay(firingAngle_fan);
  if(currentTime - zeroTime < firingDelay_fan) {
    fan_state = LOW;
  } else if(currentTime - zeroTime >= firingDelay_fan && currentTime - zeroTime < firingDelay_fan + pulseWidth) {
    fan_state = HIGH;
  } else if(currentTime - zeroTime >= firingDelay_fan + pulseWidth) {
    fan_state = LOW;
  }

  digitalWrite(Light, light_state);
  digitalWrite(Fan, fan_state);

  client.loop();
  
}
void toggle() {
  zeroTime = millis();
}

void onMessage(char* topic, byte* payload, unsigned int length) {
    
    if(strcmp(topic,TOPIC_LIGHT)==0) {
      if(payload[0] == 'o') {
        if(payload[1] == 'f') {
          digitalWrite(Light, 0x00);
        }
      } else {
        int val = (int) payload[0] - 48;
        firingAngle_light = val*30;
      }
      Serial.print("Firing light: ");
      Serial.println(firingAngle_light);
    }

    if(strcmp(topic,TOPIC_FAN)==0) {
      if(payload[0] == 'o') {
        if(payload[1] == 'f') {
          digitalWrite(Fan, 0x00);
        }
      } else {
        int val = (int) payload[0] - 48;
        firingAngle_fan = val*30;
      }
      Serial.print("Firing fan: ");
      Serial.println(firingAngle_fan);
    }

    if(strcmp(topic,TOPIC_SWITCH)==0) {
      if(payload[0] == 'o') {
        if(payload[1] == 'f') {
          digitalWrite(Switch, 0x00);
        } else {
          digitalWrite(Switch, 0x01);
        }
      }
    }
}
