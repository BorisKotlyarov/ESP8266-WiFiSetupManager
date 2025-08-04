#include <WiFiSetupManager.h>

WiFiSetupManager wifiManager;

void setup()
{
    Serial.begin(115200);
    wifiManager.begin(); // Запускаем AP + веб-сервер
}

void loop()
{
    // Обрабатываем запросы без блокировки
    if (wifiManager.process())
    {
        // Получена новая конфигурация
        WiFiSetupManager::Config conf = wifiManager.getConfig();

        Serial.println("New configuration received:");
        Serial.print("SSID: ");
        Serial.println(conf.SSID);

        // Здесь можно подключиться к WiFi
        WiFi.begin(conf.SSID, conf.password);
    }

    // Ваш основной код может выполняться здесь
    static unsigned long last = 0;
    if (millis() - last > 1000)
    {
        last = millis();
        Serial.print("Status: ");
        Serial.println(wifiManager.getStatus());
    }
}