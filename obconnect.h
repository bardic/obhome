#ifndef _OBCONNECT_H_
#define _OBCONNECT_H_

#include <Arduino.h>
#include "ESP8266WiFi.h"

class OBconnect
{
public:
    OBconnect();
    IPAddress setupWifi();
    void updateWifiState(void (*draw)(char msg[]));
};

#endif