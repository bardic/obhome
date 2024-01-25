#include "obreset.h"

int idx;
String delim;

String action;
String target;
String value;

OBrest::OBrest()
{
    this->delim = "/";
    this->idx = 0;
}

OBrest::Response OBrest::parse(char *msg)
{
    Serial.println("Parse:");
    Serial.println(msg);
    char *d = strtok(msg, "/");
    int idx = 0;

    while (d != NULL)
    {
        Serial.println(d);

        if (idx == 0)
        {
            this->response.action = d;
        }

        if (idx == 1)
        {
            this->response.store = d;
        }

        if (idx == 2)
        {
            this->response.val = d;
        }

        idx++;

        d = strtok(NULL, "/");
    }

    Serial.println("Response:");
    Serial.print("Action: ");
    Serial.println(response.action);
    Serial.print("Store: ");
    Serial.println(response.store);
    Serial.print("Value: ");
    Serial.println(response.val);

    return this->response;
}