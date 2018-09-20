#include "MqttServer.h"

using namespace std;

MqttServer::MqttServer() {
    espClient = new WiFiClient();
    mqttClient = new PubSubClient(*espClient);
    mqttClient->setServer(MQTT_SERVER, MQTT_PORT);
    mqttClient->setCallback([this] (char* topic, byte* payload, unsigned int length) { this->onMessage(topic, payload, length); });
}

void MqttServer::connect() {
    Serial.println("Attempting connection to Tesseract...");
    while(!mqttClient->connected()) {
        if(mqttClient->connect("ESP_52F5B5")) {
            Serial.println("\nConnected!");
        } else {
            Serial.print(".");
            delay(1000);
        }
    }
}

void MqttServer::initialize() {
    mqttClient->subscribe(TOPIC_SUB);
    sendMessage("Good to be here");
}

void MqttServer::onMessage(char* topic, byte* payload, unsigned int length) {
    Serial.print(topic);
    Serial.print(": ");
    for(unsigned int i = 0; i < length; i++) {
        Serial.write(payload[i]);
    }
    Serial.println("");
}

void MqttServer::sendMessage(char* payload) {
    Serial.print("Publishing: ");
    Serial.println(payload);
    mqttClient->publish(TOPIC_PUB, payload);
}

void MqttServer::sendMessage(String payload) {
    char char_payload[25];
    payload.toCharArray(char_payload, payload.length()+1);
    Serial.print("Publishing: ");
    Serial.println(char_payload);
    mqttClient->publish(TOPIC_PUB, char_payload);
}

void MqttServer::handleClient() {
    mqttClient->loop();
}
