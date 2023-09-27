#pragma once
#include <Arduino.h>
#include <LittleFS.h>
#include <string.h>

class MY_FS
{
private:
    /* data */
public:
    MY_FS(/* args */);
    ~MY_FS();

    static void listDir(Print& p, const char* dirname);
    // Output File data to an object derived from Print interface (like Serial).

    static bool WriteFile(const char* path, const String& data);

    static bool ReadFile(const char* path, String& data);
};
