#pragma once
#include <vector>

int analogRead(unsigned char pin);

void provideDataForAnalogPin(unsigned char pin, int min, int max, int step);

void resetPins();
