#include <Arduino.h>
#include "webseite.h"
#include "settings.h"
#include "funktionen.h"

#define INTERRUPT_INTERVAL 250 // interrupt entprellzeit
#include <WiFiManager.h>       // https://github.com/tzapu/WiFiManager

#include <tr064.h>

WiFiManager wm;

String tr064_service = "urn:dslforum-org:service:X_VoIP:1";

uint32_t lastrun;
TR064 tr064_connection(FRITZBOX_PORT, s_fritzIP, s_user, s_password);

void handleRing();

void IRAM_ATTR handleInterrupt()
{ // Button Interrupt
  if (millis() - i_lastinterrupt >= INTERRUPT_INTERVAL)
  {
    interrupt++;
    i_lastinterrupt = millis();
  }
}

//===============================================================
// This routine is the conf page
//===============================================================
void handleConfig()
{
  debugprintln("[HTTP] handle conf page");
  String s = CONF_page;
  s.replace("s_ringtime", s_ringtime);
  s.replace("s_interval", s_interval);
  if (s_active == "on")
    s.replace("s_active", "checked");
  else
    s.replace("s_active", "");
  s.replace("s_user", s_user);
  s.replace("s_password", s_password);
  s.replace("s_fbip", s_fritzIP);
  s.replace("s_port", s_fritzPort);
  wm.server->send(200, "text/html", s);
}

//===============================================================
// This routine is executed when you press submit
//===============================================================
void handleForm()
{
  // lade Interval
  s_interval = wm.server->arg("input_interval");
  interval = s_interval.toInt();
  writeFile(LittleFS, "/interval.txt", s_interval.c_str());

  // Lade Ringtime
  s_ringtime = wm.server->arg("input_ringtime");
  ringtime = s_ringtime.toInt();
  writeFile(LittleFS, "/ringtime.txt", s_ringtime.c_str());

  // Lade Aktiv Status
  // String tmp_active = s_active;
  s_active = wm.server->arg("input_active");
  writeFile(LittleFS, "/active.txt", s_active.c_str());

  // Lade FB User
  s_user = wm.server->arg("input_user");
  writeFile(LittleFS, "/user.txt", s_user.c_str());

  // Lade FB Passwort
  s_password = wm.server->arg("input_password");
  writeFile(LittleFS, "/password.txt", s_password.c_str());

  // Lade FB IP
  s_fritzIP = wm.server->arg("input_fbip");
  writeFile(LittleFS, "/ip.txt", s_fritzIP.c_str());

  // Lade FB Port
  s_fritzPort = wm.server->arg("input_port");
  FRITZBOX_PORT = s_fritzPort.toInt();
  writeFile(LittleFS, "/fritzport.txt", s_fritzPort.c_str());

  wm.server->sendHeader("Location", "/conf");
  wm.server->send(302, "text/plain", "Update -- Press Back Button");
  // if (s_active == "on" && tmp_active == "")
  //   ESP.restart();
}

void setup()
{
  wm.autoConnect("ESP-TuerKlingel");
  wm.startWebPortal();
  wm.server->on("/conf", handleConfig);
  wm.server->on("/action_page", handleForm);

  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TRIGGER_PIN), handleInterrupt, FALLING);

#ifdef debug
  Serial.begin(115200);
#endif
  debugprintln("\n Starting");
  debugprintln(WiFi.localIP());

  loadfiles();
  lastrun = millis();
}

void loop()
{
  wm.process(); // Webhandler

  if (millis() - lastrun >= 10000) // debug lauf
  {
    debugprintln("");
    debugprint("sek10: ");

    lastrun = millis();
  }

  // Klingeln wenn aktiv
  if (s_active == "on")
    handleRing();
}

void handleRing()
{
  if (interrupt > 0)
  {
    if (millis() - lastpress >= interval && !ringactive)
    {
      lastpress = millis();
      debugprintln("Interrupt :) && Start :D");
      tr064_connection.setServer(FRITZBOX_PORT, s_fritzIP, s_user, s_password);

      if (tr064_connection.state() < 0)
      {
        debugprintln("Verbindung aufbauen");
        tr064_connection.init();
      }
      debugprintln("Verbindung da");
      debugprintln(millis() / 1000);

      String call_params[][2] = {{"NewX_AVM-DE_PhoneNumber", "**9"}};

      tr064_connection.action(tr064_service, "X_AVM-DE_DialNumber", call_params, 1);
      ringactive = true;
      ringstart = millis();
      debugprintln(millis() / 1000);
    }
    interrupt = 0;
  }
  if (ringactive && millis() - ringstart >= ringtime)
  {
    ringactive = false;
    debugprintln("Ende...");
    debugprintln(millis() / 1000);
    tr064_connection.action(tr064_service, "X_AVM-DE_DialHangup");
  }
}
