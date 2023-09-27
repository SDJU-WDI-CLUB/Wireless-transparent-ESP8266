#include "MY_FS.h"

MY_FS::MY_FS(/* args */) {
}

MY_FS::~MY_FS() {
}

void MY_FS::listDir(Print& p, const char* dirname) {
    p.printf("Listing directory: %s\n", dirname);
    Dir root = LittleFS.openDir(dirname);
    while (root.next())
    {
        File file = root.openFile("r");
        p.print("  FILE: ");
        p.print(root.fileName());
        p.print("  SIZE: ");
        p.print(file.size());
        file.close();
    }
}



bool MY_FS::ReadFile(const char* path, String& data) {
    if (LittleFS.exists(path))
    {
        File file = LittleFS.open(path, "r");
        if (!file)return false;

        while (file.available())
        {
            data += (char) file.read();
        }
        return true;
    }
    else return false;
}


bool MY_FS::WriteFile(const char* path, const String& data) {


    File file = LittleFS.open(path, "w");
    if (!file)return false;

    file.write(data.c_str());
    return true;
}