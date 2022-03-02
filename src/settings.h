#ifndef SETTINGS_H
    #define SETTINGS_H
    #include <Arduino.h>
    #define TRIGGER_PIN 13

    extern uint16_t interrupt;       //zaehler, ob interrupt getriggert hat
    extern uint32_t interval; //intervall fuer klingel, wie oft geklingelt werden kann
    extern uint32_t lastpress;   //laufzeitzaehler letztes klingeln
    extern uint32_t ringtime; //wie lange geklingelt wird
    extern uint32_t ringstart;       //variable wann klingeln losging
    extern uint32_t i_lastinterrupt; //Variable letzter Interrupt erkannt
    extern boolean ringactive;  //Schalter, ob klingelt oder nicht
    extern String s_ringtime;   //Ringtime als String
    extern String s_interval;   //Interval als String
    extern String s_active;     //Active Status als String
    extern String s_user;     //User für FritzBox
    extern String s_password;     //Passwort für Fritzbox user
    extern String s_fritzIP;  //Fritzbox IP
    extern uint16_t FRITZBOX_PORT; //Fritzbox Port
    extern String s_fritzPort; //String für Fritzbox Port

#endif