// WebGui.h
/*
#ifndef _WEBGUI_h
#define _WEBGUI_h

#include "Config.h"

#include "ControlerInterface.h"
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WebSocketsServer.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

class WebGui :public ControlerInterface
{
public:
    AsyncWebServer* server;
    WebSocketsServer* webSocket;
    void everyLoop(); //put me in loop
    void init();
    void show(DynamicJsonDocument json);

};
#endif



                  */