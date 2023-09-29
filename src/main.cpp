#include <Arduino.h>
#include <init.h>
#include <string>
#include "ESPAsyncUDP.h"
#include "erom.h"

AsyncUDP udp;
EEPROMManager eepromManager(1024);
std::string SSID("Test");
std::string password("12345678");

void setup() {
    Serial.begin(2000000);
    Serial.setTimeout(10);
    Screen.init();
    uint8 custom = eepromManager.readByte(0);
    if (custom == 1) {
        eepromManager.readString(64, 64, SSID);
        eepromManager.readString(128, 64, password);
    }
    baseInit(SSID.c_str(), password.c_str(), WiFiMode::WIFI_AP);

    udp.listen(8080);

    udp.onPacket([](AsyncUDPPacket packet) {
        Serial.write(packet.data(), packet.length());
    });
}

uint8 buf[1450] = {0};

void loop() {
    if (Serial.available()) {
        auto len = Serial.readBytes(buf, 1450);
        if (len > 6 && (buf[0] == '+' && buf[1] == '=') &&
            (buf[len - 4] == '=' && buf[len - 3] == '+')) {
            SSID.clear();
            password.clear();
            int8 index = -1;
            for (int8 i = 2; i < len - 4; ++i) {
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
                SSID.push_back(buf[i]);
            }
            for (int i = index + 1; i < len - 4; ++i) {
                password.push_back(buf[i]);
            }
            eepromManager.writeByte(0, 1);
            eepromManager.writeString(64, SSID.c_str());
            eepromManager.writeString(128, password.c_str());
            connectWifi(String(SSID.c_str()), String(password.c_str()), true);
            return;
        }
        udp.broadcast(buf, len);
    }
}