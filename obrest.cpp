#include "obreset.h"

int idx;
char *delim;

OBrest::OBrest()
{
    this->delim = "/";
    this->idx = 0;
}

OBrest::Response OBrest::parse(char *msg)
{
    this->response.action = "";
    this->response.store = "";
    this->response.val = "";

    char *d = strtok(msg, "/");
    int idx = 0;

    while (d != NULL)
    {
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

    if (this->response.action == "" || this->response.store == "")
    {
        return this->response;
    }

    response.valid = true;
    return this->response;
}