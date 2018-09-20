#include <ESP8266WebServer.h>

#ifndef HTTPSERVER_H
#define HTTPSERVER_H

class HttpServer {
  private: 
    int port;
    ESP8266WebServer *webServer;

    void handleRoot();
    void handleCredentials();
    void handleConfigComplete();
    void handleNotFound();

  public:
    HttpServer();
  
    void begin();

    void close();

    void handleClient();
};

#endif
