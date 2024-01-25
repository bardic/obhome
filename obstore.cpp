#include "obstore.h"
#include <SD.h>
#include <SPI.h>
#include "obreset.h"

OBstore::OBstore()
{
}

void OBstore::setupSD()
{
    Serial.print("Initializing SD card...");

    if (!SD.begin(4))
    {
        Serial.println("initialization failed!");
        while (1)
            ;
    }
    Serial.println("initialization done.");
}

OBrest::Response OBstore::read(OBrest::Response resp)
{
    Serial.print("Read ");
    Serial.println(resp.store);

    OBrest::Response res;

    File txtFile = SD.open(resp.store);
    if (!txtFile)
    {
        Serial.print("error opening ");
        Serial.println(resp.store);
        while (1)
            ;
    }

    char aRecord[30];

    byte recordNum;
    byte charNum;
    while (txtFile.available())
    {
        char inChar = txtFile.read(); // get a character
        Serial.println(inChar);
        if (inChar != '\n') // if it is a newline
        {

            aRecord[charNum] = inChar; // add character to record
            charNum++;                 // increment character index
            aRecord[charNum] = '\0';   // terminate the record
        }
    }

    res.store = resp.store;
    res.val = aRecord;

    txtFile.close();

    return res;
}

OBrest::Response OBstore::write(OBrest::Response resp)
{
    OBrest::Response res;

    File txtFile = SD.open(resp.store, FILE_WRITE);
    if (!txtFile)
    {
        Serial.print("error opening ");
        Serial.println(resp.store);
        while (1)
            ;
    }

    txtFile.println(resp.val);

    res.store = resp.store;
    res.val = resp.val;
    txtFile.close();

    return res;
}