#include "obconnect.h"

// Router
#define ssid "NETGEAR74"
#define password "noteandcircuit"

WiFiServer server(8888);
WiFiClient serverClients[1];

String readString;

OBconnect::OBconnect()
{
}

IPAddress OBconnect::setupWifi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());

  server.begin();
  server.setNoDelay(true);

  Serial.println("server started");

  return WiFi.localIP();
}

void OBconnect::updateWifiState(void (*draw)(char msg[]))
{
  WiFiClient client = server.available();

  if (client)
  {
    if (client.connected())
    {
      Serial.println("Client Connected");
    }

    char msg[64];
    while (client.connected())
    {
      msg[0] = '\0';
      int idx = 0;
      while (client.available())
      {
        // read data from the connected client
        char c = client.read();
        if (c != '\n' && c != '\r') 
        {
          msg[idx] = c;
          idx++;
          msg[idx] = '\0';
        }
      }
      if (msg[0] != '\0')
      {
        draw(msg);
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}