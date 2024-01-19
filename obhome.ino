#include <SoftwareSerial.h>
#include <SD.h>
#include "esp8266.h"

// Router
#define ssid "NETGEAR74"
#define password "noteandcircuit"

// Server
#define serverPort 8081

Esp8266 wifi;
File f;

int pin = 10;
int idx = 0;

String action;
String target;
String value;

void setup()
{
  pinMode(pin, OUTPUT);
  delay(2000);

  Serial.begin(115200);

  setupSD();
  setupWifi();
}

void loop()
{
  updateWifiState(wifi.getState());
}

// setup
void setupSD()
{
  Serial.print("Initializing SD card...");

  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");
}

void setupWifi()
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

void updateWifiState(int state)
{
  switch (state)
  {
    case WIFI_NEW_MESSAGE:
      Serial.println(String(wifi.getWorkingID()) + ":" + wifi.getMessage()); // debug
      wifi.setState(WIFI_IDLE);
      ParseMsg(wifi.getMessage());
      break;
    case WIFI_CLOSED: // just print which connect is close, won't reconnect
      Serial.println(String(wifi.getFailConnectID()) + ":connect closed!");
      wifi.setState(WIFI_IDLE);
      break;
    case WIFI_IDLE:
      {
        int state = wifi.checkMessage();
        wifi.setState(state);
        break;
      }
    case WIFI_CLIENT_ON: // if a client is connected ,say hello to it
      wifi.sendMessage(wifi.getWorkingID(), "hello, this is OBhome.\n");
      wifi.setState(WIFI_IDLE);
      break;
  }
}

void ParseMsg(String msg)
{
  idx = msg.indexOf(":");
  action = msg.substring(0, idx);
  msg.remove(0, idx+1);
  idx = msg.indexOf(":");
  target = msg.substring(0, idx);
  msg.remove(0, idx+1);
  idx = msg.indexOf(":");
  value = msg.substring(0, idx);

  target.trim();
  value.trim();
  action.trim();

  Serial.print("Action: ");
  Serial.print(action);
  Serial.print("; Target: ");
  Serial.print(target);
  Serial.print("; Value: ");
  Serial.print(value);

  if(action == "post"){
    Post();
  }

  if(action == "put"){
    Put();
  }

  if(action == "get"){
    Get();
  }

  if(action == "delete"){
    Delete();
  }
}

void Post()
{
	f = SD.open(target, FILE_WRITE);
  if (f) {
    f.println(value);
    f.close();
  } else {
    Serial.println("error opening file");
  }
}

void Put()
{
	SD.remove(target);
	Post();
}

void Delete()
{
	SD.remove(target);
}

void Get()
{ 
	f = SD.open(target, FILE_READ);
  if (f) {
    while (f.available()) {
      wifi.sendMessage(wifi.getWorkingID(), f.readString());
    }
    f.close();
  } else {
    Serial.println("error opening file");
  }
}
