#pragma once

#include <c_types.h>
#include <string>
#include "EEPROM.h"
#include "HardwareSerial.h"

class EEPROMManager {
public:
    explicit EEPROMManager(uint16 size);

    ~EEPROMManager();

    void writeByte(uint16 address, uint8 data);

    void writeString(uint16 address, const char *string);

    void writeString(uint16 address, const std::string &string) {
        writeString(address, string.c_str());
    }

    uint8 readByte(uint16 address);

    void readString(uint16 address, uint16 length, std::string &string) {
        int len = 1;
        string.clear();
        uint8 data = readByte(address++);
        while (data != '\0' && len <= length){
            string.push_back(data);
            data = readByte(address++);
            len++;
        }
    }

    template<typename T>
    void readData(uint16 address, T &data) {
        EEPROM.get<T>(address, data);
    }

    template<typename T>
    void writeData(uint16 address, T &data) {
        EEPROM.put<T>(address, data);
        EEPROM.commit();
    }

    void clear();

private:
    int size = 0;
    void writeByte(uint16 address, uint8 data, bool ignore);
};
