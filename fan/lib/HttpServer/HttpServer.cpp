#include "HttpServer.h"
#include <HerculesParams.h>
#include <HerculesWireless.h>
#include <ArduinoJson.h>

using namespace std;

HttpServer::HttpServer() {
    this->port = 80;
    webServer = new ESP8266WebServer(this->port);
    webServer->on("/", HTTP_GET, std::bind(&HttpServer::handleRoot, this));
    webServer->on("/auth", HTTP_POST, std::bind(&HttpServer::handleCredentials, this));
    webServer->on("/complete", HTTP_GET, std::bind(&HttpServer::handleConfigComplete, this));
    webServer->onNotFound(std::bind(&HttpServer::handleNotFound, this));
}

void HttpServer::handleRoot() {
    HerculesWireless wireless;
    Credentials cred = wireless.getCredentials();
    webServer->send(200, "text/html", cred.toJSON());
}

void HttpServer::handleCredentials() {
    Credentials cred;
    HerculesWireless wireless;
    String ssid = webServer->arg("ssid");
    String psk  = webServer->arg("psk");
    char* p_ssid = cred.ssid; 
    char* p_psk = cred.psk;
    ssid.toCharArray(p_ssid, 15);
    psk.toCharArray(p_psk, 15);
    wireless.putCredentials(cred);
    webServer->send(200, "application/json", "{\"status\": \"200\"}");
}

void HttpServer::handleConfigComplete() {
    HerculesParams::setConfigured(true);
    Serial.print(HerculesParams::isConfigured());
    webServer->send(200, "application/json", "{\"status\": \"200\"}");
    ESP.restart();
}

void HttpServer::handleNotFound() {
    webServer->send(404, "text/html", "Error 404!");
}

void HttpServer::begin() {
    webServer->begin();
}

void HttpServer::close() {
    webServer->close();
}

void HttpServer::handleClient() {
    webServer->handleClient();
}
