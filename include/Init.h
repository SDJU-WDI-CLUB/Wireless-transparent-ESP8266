#pragma once
#include <ESP8266WiFi.h>
#include <config.h>
#include <string>
#include <LVGL.h>
#include "ArduinoJson.h"
#include "MY_FS.h"
String WifiSSID = "Tool9";
String WifiPSWD = "123456789";
WiFiMode WifiMode = WiFiMode::WIFI_AP;


bool baseInit() {
    //串口初始化
    Serial.begin(2000000);
    Serial.setTimeout(10);
    Screen.init();

    // wifi连接
    WiFi.mode(WifiMode);

    WiFi.begin(WifiSSID, WifiPSWD);
    Screen.ShowStr(0, "Connecting:" + WifiSSID);
    Screen.ShowStr(1, "WifiSpeed:2.4G");
    Screen.ShowStr(2, "Password:" + WifiPSWD);

    while (WiFi.status() != WL_CONNECTED)
    {

        switch (WiFi.status())
        {
        case WL_WRONG_PASSWORD:
            Screen.ShowStr("PassWord err!");

            return false;
        case WL_NO_SSID_AVAIL:
            Screen.ShowStr("Don't have this Wifi!");

            return false;
            break;
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
