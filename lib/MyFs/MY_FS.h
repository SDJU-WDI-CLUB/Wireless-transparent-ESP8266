#pragma once
#include <Arduino.h>
#include <LittleFS.h>
#include <cstring>

class MY_FS
{
public:
    MY_FS();
    ~MY_FS();

    static void listDir(Print& p, const char* dirname);

    static bool WriteFile(const char* path, const String& data);

    static bool ReadFile(const char* path, String& data);
};
