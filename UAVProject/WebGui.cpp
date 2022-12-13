#include "WebGui.h"
#if 0




void webSocketEvent(uint8_t num, WStype_t type, uint8_t* paylode, size_t welength) {

    switch (type) {

    case WStype_DISCONNECTED:
        Serial.printf("[%u] Disconnected!\n", num);
        break;

    case WStype_CONNECTED:
        Serial.printf("[%u] Connected\n", num);
        break;

    case WStype_TEXT:
        Serial.printf("[%u] get Text: %s\n", num, paylode);
        char* message = (char*)paylode;
        Serial.printf(message);
        //webSocket.sendTXT(num, paylode, welength);    

    }
}

void WebGui::init()
{
    server = new AsyncWebServer(80);
    webSocket = new WebSocketsServer(81);

    //handle file storge for webSite
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        Serial.println("The 'SPIFFS' give acsses to file system (html etc.)");
        return;
    }

    //handle wifi and make hot-spot.
    WiFi.softAP(WIFI_SSID /*,WIFI_PASSWORD*/); //password is optional
    IPAddress myIP = WiFi.softAPIP();
    /*
    while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          Serial.print(".");
      }
      */
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    // Route for root / web page
    server->on("/", HTTP_GET, [](AsyncWebServerRequest* request) {request->send(SPIFFS, "/index.html"); });
    server->begin();

    // start the websocket server
    webSocket->begin();
    webSocket->onEvent(webSocketEvent);

    //Make DNS so in chrome you jest type 'esp32.local'
    if (!MDNS.begin(WIFI_LOCAL)) {
        Serial.println("Error starting mDNS");
        return;
    }
    else Serial.println("mDNS responder started!\ntype in you'r browser 'esp32.local'.");

    Serial.println("setup complete!");

}

void WebGui::everyLoop() {
    webSocket->loop();
}


void WebGui::show(DynamicJsonDocument json) {
    //json.shrinkToFit();
    char str[MSG_BUF_SIZE];
    serializeJson(json, str);
    if (webSocket->connectedClients() != 0)
        webSocket->broadcastTXT(str, MSG_BUF_SIZE);
    else Serial.println("No body conected!");
    //webSocket->sendTXT(0, str, MSG_BUF_SIZE);
    delete str;
}
#endif // 0