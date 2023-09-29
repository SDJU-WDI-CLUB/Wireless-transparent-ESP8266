#include "erom.h"

EEPROMManager::EEPROMManager(uint16 size) {
    this->size = size;
    EEPROM.begin(size);
}

EEPROMManager::~EEPROMManager() = default;


void EEPROMManager::writeByte(uint16 address, uint8 data) {
    EEPROM.write(address, data);
    EEPROM.commit();
}

void EEPROMManager::writeByte(uint16 address, uint8 data, bool ignore) {
    EEPROM.write(address, data);
}

void EEPROMManager::writeString(uint16 address, const char *string) {
    while (*string != '\0') {
        writeByte(address++, *(string++), true);
    }
    writeByte(address, '\0');
}

uint8 EEPROMManager::readByte(uint16 address) {
    return EEPROM.read(address);
}

void EEPROMManager::clear() {
    memset(EEPROM.getDataPtr(), 0, size);
    EEPROM.commit();
}
