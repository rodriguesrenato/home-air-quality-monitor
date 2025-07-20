#include "Utils.h"

unsigned long CalcDt(unsigned long ts)
{
    unsigned long tm = millis();
    if (tm < ts)
    {
        return tm + ((-1UL) - ts);
    }
    return tm - ts;
}

unsigned long CalcDtUs(unsigned long ts)
{
    unsigned long tm = micros();
    if (tm < ts)
    {
        return tm + ((-1UL) - ts);
    }
    return tm - ts;
}

void PrintDebug(String className, String functionName, String message)
{
    if (Serial)
    {
        Serial.println("[" + String(millis()) + "|" + className + "::" + functionName + "] " + message);
    }
}