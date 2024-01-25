#ifndef _OBCONNECT_H_
#define _OBCONNECT_H_

#include <Arduino.h>

class OBconnect
{
public:
    OBconnect();
    void setupWifi();
    char *updateWifiState();
};

#endif