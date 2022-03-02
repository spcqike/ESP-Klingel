#include <Arduino.h>
#include "funktionen.h"
#include "settings.h"

void writeFile(fs::FS &fs, const char *path, const char *message)
{
  debugprint("write File: ");
  debugprintln(path);
  File file = fs.open(path, "w");
  if (!file)
  {
    debugprintln("- failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    debugprint("- file written ");
  }
  else
  {
    debugprint("- write failed ");
  }
  debugprintln(message);
}

String readFile(fs::FS &fs, const char *path)
{
  debugprint("read File: ");
  debugprintln(path);
  File file = fs.open(path, "r");
  if (!file || file.isDirectory())
  {
    debugprintln("- empty file or failed to open file");
    return String("error");
  }
  debugprint("- read from file: ");
  String fileContent;
  while (file.available())
  {
    fileContent += String((char)file.read());
  }
  debugprintln(fileContent);
  return fileContent;
}

void loadfiles()
{
  //Lade Filesystem
  if (!LittleFS.begin())
  {
    debugprintln("An Error has occurred while mounting LittleFS");
    return;
  }

  //Lade Ringtime
  s_ringtime = readFile(LittleFS, "/ringtime.txt");
  if (s_ringtime == "error")
  {
    debugprintln("nicht da, erstelle");
    writeFile(LittleFS, "/ringtime.txt", String(ringtime).c_str());
  }
  else
  {
    ringtime = s_ringtime.toInt();
  }

  //Lade Interval
  s_interval = readFile(LittleFS, "/interval.txt");
  if (s_interval == "error")
  {
    debugprintln("nicht da, erstelle");
    writeFile(LittleFS, "/interval.txt", String(interval).c_str());
  }
  else
  {
    interval = s_interval.toInt();
  }

  //Lade Aktivstatus
  s_active = readFile(LittleFS, "/active.txt");

  //Lade FB User
  s_user = readFile(LittleFS, "/user.txt");
  if (s_user == "error")
  {
    debugprintln("nicht da, erstelle");
    s_user = "admin";
    writeFile(LittleFS, "/user.txt", s_user.c_str());
    
  }

  //Lade FB Passwort
   s_password = readFile(LittleFS, "/password.txt");
  if (s_password == "error")
  {
    debugprintln("nicht da, erstelle");
    s_password="password";
    writeFile(LittleFS, "/password.txt", s_password.c_str());
  }

  //Lade FB IP
  s_fritzIP = readFile(LittleFS, "/ip.txt");
  if (s_fritzIP == "error")
  {
    debugprintln("nicht da, erstelle");
    s_fritzIP = "192.168.178.1";
    writeFile(LittleFS, "/ip.txt", s_fritzIP.c_str());
  }

  //Lade Fritzbox Port
  s_fritzPort = readFile(LittleFS, "/fritzport.txt");
  if (s_fritzPort == "error")
  {
    debugprintln("nicht da, erstelle");
    writeFile(LittleFS, "/fritzport.txt", String(FRITZBOX_PORT).c_str());
  }
  else
  {
    FRITZBOX_PORT = s_fritzPort.toInt();
  }

}


