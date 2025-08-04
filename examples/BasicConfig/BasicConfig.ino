#include <WiFiSetupManager.h>

WiFiSetupManager wifiSetup("MyDeviceConfig");

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting configuration portal...");

    // Blocking mode - will wait config from server
    wifiSetup.runBlocking();

    // After Blocking mode
    Serial.println("WiFi configured!");
    WiFiSetupManager::Config conf = wifiSetup.getConfig();

    Serial.print("SSID: ");
    Serial.println(conf.SSID);
    Serial.print("Password: ");
    Serial.println(conf.password);

    // connect to WiFi
    WiFi.begin(conf.SSID, conf.password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected!");
}

void loop()
{
    // your primary code here
}