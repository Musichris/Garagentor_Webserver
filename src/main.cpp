#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include <LittleFS.h>

const char *ssid = "Homies Crib";
const char *password = "1156617419567636";

WebServer server(80);

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Verbinde mit WiFi...");
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("Verbunden mit WiFi!");
            Serial.print("IP-Adresse: ");
            Serial.println(WiFi.localIP());
        }
    }
    if (!LittleFS.begin())
    {
        Serial.println("LittleFS konnte nicht gestartet werden");
        return;
    }
    server.on("/", HTTP_GET, []()
              {
        if (LittleFS.exists("/Garagentor.html")) {
            File file = LittleFS.open("/Garagentor.html", "r");
            server.streamFile(file, "text/html");
            file.close();
        } else {
            server.send(404, "text/plain", "Datei nicht gefunden");
        } });

    server.begin();
}

void loop()
{
    server.handleClient();
    delay(1000);
    Serial.println("Server läuft...");
}