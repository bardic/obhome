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
    } response;
    OBrest::Response parse(char *msg);

    char *action;
    char *target;
    char *value;

private:
    int idx;
    char *delim;
};

#endif