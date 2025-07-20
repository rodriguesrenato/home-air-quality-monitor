#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

unsigned long CalcDt(unsigned long ts);
unsigned long CalcDtUs(unsigned long ts);
void PrintDebug(String className, String functionName, String message);

#endif
