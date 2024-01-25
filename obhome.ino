#include <SoftwareSerial.h>
#include "obreset.h"
#include "obstore.h"
#include "obconnect.h"

int pin = 10;

int goalTemp = 0;
int defaultTemp = 10;

char TEMP[] = "TEMP";
char historyFile[] = "HIST";

OBrest rest;
OBstore store;
OBconnect conn;

void setup()
{
  delay(2000);
  Serial.begin(115200);
  store.setupSD();
  conn.setupWifi();
  delay(2000);
  // checkDefaults();
}

void loop()
{

  // digitalWrite(pin,HIGH);

  // updateWifiState(wifi.getState());

  char *msg = conn.updateWifiState();

  OBrest::Response r = rest.parse(msg);

  if (!r.valid)
  {
    // Serial.println("Not valid");
    return;
  }

  if (strcmp(r.action, "post") == 0)
  {
    Serial.println("Write");
    store.write(r.store, r.val);
    // Serial.println(r.store);
    // Serial.println(r.val);
  }

  if (strcmp(r.action, "get") == 0)
  {
    Serial.println("Get");
    OBrest::Response r2 = store.read(r);
    Serial.println(r2.store);
    Serial.println(r2.val);
  }

  // currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  // if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  // {
  //   GetLiveTemp();
  //   startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
  // }

  // GetLiveTemp();
}

void GetLiveTemp()
{
  int val;
  double data;
  val = analogRead(0);
  data = (double)val * (5 / 10.24); // convert the voltage to temperture

  Serial.print("Live Temp: ");
  Serial.println(data);
}