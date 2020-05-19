#pragma once

#include <AnalogSensor.h>

namespace ESP32BBQProbe {
    class ThermalProbe {
        public:
            ThermalProbe(AnalogSensor, const double);
        private:
            AnalogSensor sensor;
            const double steinhartCoeficients[3];
    };
}