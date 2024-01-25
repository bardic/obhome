#ifndef _OBSTORE_H_
#define _OBSTORE_H_

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "obreset.h"

class OBstore
{
public:
    OBstore();
    void setupSD();
    OBrest::Response read(OBrest::Response resp);
    void write(char store[], char val[]);

private:
    File myFile;
};

#endif