#ifndef _OBSTORE_H_
#define _OBSTORE_H_

#include <Arduino.h>
#include <SPI.h>

class OBstore
{
public:
    OBstore();
    void setupSD();
    char *read(char store[]);
    void write(char store[], char val[]);
};

#endif