#ifndef MQTT_SERVER_H
#define MQTT_SERVER_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_SERVER "cravis"
#define MQTT_PORT 1883

#define TOPIC_SUB "hercules/sub/2934FCD34"
#define TOPIC_PUB "hercules/pub/2934FCD34"

class MqttServer {

    private:
        WiFiClient *espClient;
        PubSubClient *mqttClient;

        void onMessage(char* topic, byte* payload, unsigned int length);

    public:
        MqttServer();
        void connect();
        void initialize();
        void sendMessage(char*);
        void handleClient();
};

#endif
