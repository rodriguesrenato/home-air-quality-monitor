#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

unsigned long calcDt(unsigned long ts);
unsigned long calcDtUs(unsigned long ts);
void printDebug(String className, String functionName, String message);

#endif
