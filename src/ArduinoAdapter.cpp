#include <ArduinoAdapter.h>

#ifdef TEST_HARNESS
#include "FakeArduino.h"
#else
#include "Arduino.h"
#endif

int ESP32BBQProbe::readFromNativeSensor(unsigned char pin) {
    return analogRead(pin);
}
