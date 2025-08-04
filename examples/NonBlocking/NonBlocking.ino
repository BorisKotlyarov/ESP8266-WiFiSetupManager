#include <WiFiSetupManager.h>

WiFiSetupManager wifiManager;

void setup()
{
    Serial.begin(115200);
    wifiManager.begin(); // Run the AP + Http server
}

void loop()
{
    // Handle requests without Blocking
    if (wifiManager.process())
    {
        // received New configuration
        WiFiSetupManager::Config conf = wifiManager.getConfig();

        Serial.println("New configuration received:");
        Serial.print("SSID: ");
        Serial.println(conf.SSID);

        // Connect to WiFi here
        WiFi.begin(conf.SSID, conf.password);
    }

    // Your primary code can be execute here
    static unsigned long last = 0;
    if (millis() - last > 1000)
    {
        last = millis();
        Serial.print("Status: ");
        Serial.println(wifiManager.getStatus());
    }
}