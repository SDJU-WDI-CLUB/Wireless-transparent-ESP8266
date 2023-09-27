#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <LVGL.h>
#include <Init.h>
#include <vector>
#include "ESPAsyncUDP.h"



AsyncUDP udp;



void setup() {
    baseInit();

    udp.listen(8080);

    udp.onPacket([](AsyncUDPPacket packet) {
        Serial.write(packet.data(), packet.length());
        });
}

uint8_t buf[1450] = { 0 };

void loop() {
    if (Serial.available())
    {
        auto lenth = Serial.readBytes(buf, 1450);
        udp.broadcast(buf, lenth);
    }
}