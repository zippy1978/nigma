#ifndef HTTP_h
#define HTTP_h

#include <ESP8266WiFi.h>

#include "Lock.h"
#include "Settings.h"

// Parameters
#define HTTP_PORT 80
#define HTTP_TIMEOUT_MS 2000

struct HTTPRequest {
    String method;
    String path;
};

class HTTP
{
private:
    WiFiServer server;
    Settings *settings;
    Lock *lock;
    void home(WiFiClient *client);
    void sendHeader(WiFiClient *client, int status, String contentType);
    void handleRequest(WiFiClient *client, HTTPRequest httpRequest);

public:
    HTTP(Settings *settings, Lock *lock) : server(HTTP_PORT), settings(settings), lock(lock){};
    void setup(String ssid, String password);
    void listen();
    String getAddress();
    HTTPRequest parseRequest(String request);
};

#endif