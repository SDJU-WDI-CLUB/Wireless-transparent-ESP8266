#include <Arduino.h>
#include <init.h>
#include <string>
#include "ESPAsyncUDP.h"

AsyncUDP udp;

void setup() {
    baseInit("Tool9", "123456789", WiFiMode::WIFI_AP);

    udp.listen(8080);

    udp.onPacket([](AsyncUDPPacket packet) {
        Serial.write(packet.data(), packet.length());
    });
}

uint8_t buf[1450] = {0};

void loop() {
    if (Serial.available()) {
        auto len = Serial.readBytes(buf, 1450);
        if (len > 4 && (buf[0] == '+' && buf[1] == '=') &&
            (buf[len - 2] == '=' && buf[len - 1] == '+')) {
            std::string SSID;
            std::string password;
            int8 index = -1;
            for (int8 i = 2; i < len - 2; ++i) {
                if (buf[i] == ';') {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                Serial.write("Command Error.");
                return;
            }
            for (int i = 2; i < index; ++i) {
                password.push_back(buf[i]);
            }
            for (int i = index + 1; i < len - 2; ++i) {
                SSID.push_back(buf[i]);
            }
            connectWifi(String(SSID.c_str()), String(password.c_str()), true);
            return;
        }
        udp.broadcast(buf, len);
    }
}