#include <Arduino.h>
#include "settings.h"

    uint16_t interrupt=0;
    uint32_t interval=2000; 
    uint32_t lastpress=0;   
    uint32_t ringtime=5000; 
    uint32_t ringstart=0;       
    uint32_t i_lastinterrupt=0;
    boolean ringactive=false;
    String s_ringtime="";
    String s_interval="";
    String s_active="";
    String s_user="";
    String s_password = "password";
    String s_fritzIP = "192.168.178.1";
    uint16_t FRITZBOX_PORT = 49000;
    String s_fritzPort="";
