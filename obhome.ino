#include <Arduino.h>
#include <U8g2lib.h>
#include "ESP8266WiFi.h"
#include "obconnect.h"
#include "obrest.h"
#include <algorithm>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/14, /* data=*/12, /* reset=*/U8X8_PIN_NONE);

IPAddress ip;

char ipAddress[64];

unsigned long tepTimer;

#define TPIN 0

uint32_t delayMS;

void setup(void)
{
  Serial.begin(115200);
  delay(2500);

  u8g2.begin();
  ip = OBconnect().setupWifi();
  WiFi.localIP().toString().toCharArray(ipAddress, 64);

  // OBstore().setupSD();
  OBrest::Response r = {};
  r.valid = false;
  draw(r);
}

void loop(void)
{
  OBconnect().updateWifiState(addMsg);

  delay(2500);
  int val;                          // save the value of LM35
  double data;                      // save the converted value of temperature
  val = analogRead(TPIN);           // Connect LM35 to analog pin and read
  data = ((double)val * 5) / 10.24; // Convert the voltage value to

  if (data > 27)
  { // If temperature is higher than 27, the buzzer starts to

    Serial.println("Too hot");
  }
  else
  { // If the temperature is lower than

    Serial.println("Too hot");
  }
  if (millis() - tepTimer > 50)
  { // Every 500 ms, serial port outputs

    tepTimer = millis();
    Serial.print("temperature: "); // Serial port outputs temperature
    Serial.print(data);            // Serial port outputs temperature

    Serial.println("C"); // Serial port output temperature
  }
}

void addTempSenor()
{
}

void addMsg(char *msg)
{
  OBrest::Response r = OBrest().parse(msg);

  Serial.print("Action: ");
  Serial.println(r.action);

  if (strcmp(r.action, "post") == 0)
  {
    Serial.println("Handle Post");
  }

  if (strcmp(r.action, "put") == 0)
  {
    Serial.println("Handle Put");
  }

  if (strcmp(r.action, "get") == 0)
  {
    Serial.println("Handle Get");
  }

  if (strcmp(r.action, "delete") == 0)
  {
    Serial.println("Handle Delete");
  }

  draw(r);
}

void draw(OBrest::Response r)
{

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_7x14B_tr);

  u8g2.setCursor(0, 30);
  u8g2.print("IP: ");
  u8g2.setCursor(25, 30);
  u8g2.print(ip);

  u8g2.setCursor(0, 60);
  u8g2.print("Msg: ");
  if (!r.valid)
  {
    u8g2.sendBuffer();
    return;
  }

  u8g2.setCursor(30, 60);
  u8g2.print(r.action);
  u8g2.print("/");
  u8g2.print(r.store);
  u8g2.print("/");
  u8g2.print(r.val);

  u8g2.sendBuffer();
}
