#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <string>

/// @brief  128 32
class LVGL : public Adafruit_SSD1306 {
private:
    static const int Charsize = 1;
    static const int MaxLine = 4;
    static const int MaxCharSzie = 21;

public:
    LVGL(int w, int h);

    ~LVGL();

    void init();

    void Clear();

    void ShowStr(const String &str);

    void ShowStr(const char *str);

    bool ShowStr(int line, const String &str);

    bool ShowStr(int line, int x, const String &str);
};

extern LVGL Screen;
