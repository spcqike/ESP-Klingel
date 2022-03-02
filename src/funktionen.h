
#ifndef FUNKTIONEN
    #define FUNKTIONEN
    #include <LittleFS.h>
    #include "settings.h"

    #define debug
    #ifdef debug
    #define debugprint(x) Serial.print(x)
    #define debugprintln(x) Serial.println(x)
    #else
    #define debugprint(x)
    #define debugprintln(x)
    #endif

    void writeFile(fs::FS &fs, const char *path, const char *message);
    String readFile(fs::FS &fs, const char *path);
    void loadfiles();
#endif