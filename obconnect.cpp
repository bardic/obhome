#include "esp8266.h"
#include "obconnect.h"

// Router
#define ssid "NETGEAR74"
#define password "noteandcircuit"

// Server
#define serverPort 8081
Esp8266 wifi;
char char_array[16];

OBconnect::OBconnect()
{
}

void OBconnect::setupWifi()
{
    wifi.begin(&Serial); // Serial is used to communicate with esp8266 module, mySerial is used to debug
    if (wifi.connectAP(ssid, password))
    {
        Serial.println("connect ap sucessful !");
    }
    else
    {
        while (true)
            ;
    }

    if (wifi.setMultiConnect())
    {
        Serial.println("set multi connect!");
    }

    if (wifi.openTCPServer(serverPort, 180))
    {
        Serial.println("open TCP Server port " + String(serverPort) + " OK!");
    }

    Serial.println("Server IP:" + wifi.getIP() + " Port:" + String(serverPort));
}

char *OBconnect::updateWifiState()
{
    int state = wifi.getState();
    char_array[0] = '\0';

    switch (state)
    {
    case WIFI_NEW_MESSAGE:
    {
        String msg = wifi.getMessage();
        int str_len = msg.length() + 1;
        msg.trim();
        msg.toCharArray(char_array, str_len);
        Serial.println("wifi messsage");
        Serial.println(char_array);
        wifi.setState(WIFI_IDLE);
        break;
    }
    case WIFI_CLOSED:
        wifi.setState(WIFI_IDLE);
        break;
    case WIFI_IDLE:
        wifi.setState(wifi.checkMessage());
        break;
    case WIFI_CLIENT_ON:
        wifi.setState(WIFI_IDLE);
        break;
    }

    return char_array;
}