#pragma once
#include <ESP8266WiFi.h>
#include <config.h>
#include <string>
#include <LVGL.h>
#include "ArduinoJson.h"
#include "MY_FS.h"

bool baseInit(const String &SSID, const String &password, const WiFiMode &mode);
bool connectWifi(const String &SSID, const String &password, const WiFiMode &mode);
bool connectWifi(const String &SSID, const String &password);
bool connectWifi(const String &SSID, const String &password, const WiFiMode &mode, bool ignored);
bool connectWifi(const String &SSID, const String &password, bool ignored);
