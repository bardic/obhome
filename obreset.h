#ifndef _OBREST_H_
#define _OBREST_H_

#include <Arduino.h>
#include <Stream.h>

class OBrest
{
public:
    OBrest();
    struct Response
    {
        char *store;
        char *action;
        char *val;
        bool valid;
    } response;
    OBrest::Response parse(char *msg);

private:
    int idx;
    char *delim;
};

#endif