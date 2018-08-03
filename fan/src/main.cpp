#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress apIP(192, 168, 24, 5);
ESP8266WebServer webServer(80);

String responseHTML = "{\"foo\":\"bar\"}";

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("[Hercules]2934FCD34", "IrisConfig");

  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();
}

void loop() {
  webServer.handleClient();
}
