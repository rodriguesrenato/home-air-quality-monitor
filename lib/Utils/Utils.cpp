#include "Utils.h"

unsigned long calcDt(unsigned long ts)
{
    unsigned long tm = millis();
    if (tm < ts)
    {
        return tm + ((-1UL) - ts);
    }
    return tm - ts;
}

unsigned long calcDtUs(unsigned long ts)
{
    unsigned long tm = micros();
    if (tm < ts)
    {
        return tm + ((-1UL) - ts);
    }
    return tm - ts;
}

void printDebug(String className, String functionName, String message)
{
    if (Serial)
    {
        Serial.println("[" + String(millis()) + "|" + className + "::" + functionName + "] " + message);
    }
}