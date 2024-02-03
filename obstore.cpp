#include "obstore.h"

OBstore::OBstore()
{
}

void OBstore::setupSD()
{
    Serial.print("Initializing SD card...");
}

char *OBstore::read(char store[])
{
    Serial.print("Read from file: ");
    Serial.print(store);
    return "test";
}

void OBstore::write(char store[], char val[])
{
    Serial.print("Write to file: ");
    Serial.println(store);
    Serial.print("Value: ");
    Serial.println(val);
}