#include "init.h"

bool
baseInit(const String &SSID, const String &password, const WiFiMode &mode) {
    //串口初始化
    Serial.begin(2000000);
    Serial.setTimeout(10);
    Screen.init();
    return connectWifi(SSID, password, mode);
}

bool
connectWifi(const String &SSID, const String &password) {
    WiFi.begin(SSID, password);
    Screen.ShowStr(0, "Connecting:" + SSID);
    Screen.ShowStr(1, "WifiSpeed:2.4G");
    Screen.ShowStr(2, "Password:" + password);

    while (WiFi.status() != WL_CONNECTED) {
        switch (WiFi.status()) {
            case WL_WRONG_PASSWORD:
                Screen.ShowStr("PassWord err!");
                return false;
            case WL_NO_SSID_AVAIL:
                Screen.ShowStr("Don't have this Wifi!");
                return false;
            default:
                break;
        }
        Serial.printf(".");
        delay(500);
    }
    Screen.clearDisplay();
    Screen.ShowStr(0, "MyIP:" + WiFi.localIP().toString());
    Screen.ShowStr(1, "Local Port:8080");
    Screen.ShowStr(2, "Protocol:UDP");
    return true;
}

bool
connectWifi(const String &SSID, const String &password, const WiFiMode &mode) {
    // wifi连接
    WiFi.mode(mode);
    return connectWifi(SSID, password);
}

bool
connectWifi(const String &SSID, const String &password, const WiFiMode &mode, bool ignored) {
    // wifi连接
    WiFi.disconnect();
    return connectWifi(SSID, password, mode);
}

bool
connectWifi(const String &SSID, const String &password, bool ignored) {
    // wifi连接
    WiFi.disconnect();
    return connectWifi(SSID, password);
}