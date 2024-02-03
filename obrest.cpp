#include "obrest.h"

int idx;
const char *delim = "/";

OBrest::OBrest()
{
}

OBrest::Response OBrest::parse(char *msg)
{
    OBrest::Response r = {};

    char *d = strtok(msg, "/");
    int idx = 0;

    while (d != NULL)
    {

        if (idx == 0)
        {
            r.action = d;
        }

        if (idx == 1)
        {
            r.store = d;
        }

        if (idx == 2)
        {
            r.val = d;
        }

        Serial.println(d);
        idx++;

        d = strtok(NULL, "/");
    }

    if (r.action == "" || r.store == "")
    {
        return r;
    }

    r.valid = true;
    return r;
}