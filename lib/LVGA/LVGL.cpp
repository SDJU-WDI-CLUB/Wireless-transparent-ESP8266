#include "LVGL.h"

LVGL Screen(128, 32);

LVGL::LVGL(int w, int h) : Adafruit_SSD1306(w, h, &Wire, -1) {}

LVGL::~ LVGL() = default;

void LVGL::init() {
    Wire.begin(D1, D2);
    if (!this->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while (true);
    }
    this->Clear();
}

void LVGL::Clear() {
    this->clearDisplay();
    this->display();
}

void LVGL::ShowStr(const String &str) {
    this->clearDisplay();
    this->setTextSize(Charsize);
    this->setTextColor(WHITE);
    this->setCursor(0, 0);
    this->println(str);
    this->display();
}

void LVGL::ShowStr(const char *str) {
    this->clearDisplay();
    this->setTextSize(Charsize);
    this->setTextColor(WHITE);
    this->setCursor(0, 0);
    this->println(str);
    this->display();
}

// 6x8
bool LVGL::ShowStr(int line, const String &str) {
    if (line >= MaxLine)
        return false;
    this->setTextSize(Charsize);
    this->setTextColor(WHITE);
    this->setCursor(0, line * 8);
    this->println(str);
    this->display();
    return true;
}

bool LVGL::ShowStr(int line, int x, const String &str) {
    if (line >= MaxLine || x >= MaxCharSzie)
        return false;

    this->setTextSize(Charsize);
    this->setTextColor(WHITE);
    this->setCursor(x * 6, line * 8);
    this->println(str);
    this->display();
    return true;
}