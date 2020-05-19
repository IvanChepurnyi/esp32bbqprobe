#pragma once

#include <ArduinoAdapter.h>

namespace ESP32BBQProbe {
    class AnalogSensor {
        double calibration[7];
        unsigned int resolution;
        double referenceVoltage;
        unsigned int referenceResistor;
        unsigned char pin;

        public:
            int readValue() const;

            double readVoltage() const;

            int readResistance() const;

            AnalogSensor(
                const unsigned char pin,
                const unsigned int resolution,
                const double referenceVoltage,
                const unsigned referenceResistor,
                const double *calibration
            );
    };

    class AnalogSensorBuilder
    {
        double calibration[7] = {0, 0, 0, 0, 0, 1, 0};
        unsigned int resolution = 4095;
        double referenceVoltage = 3.3;

        public:
            AnalogSensorBuilder withResolution(const unsigned int resolution);

            AnalogSensorBuilder withReferenceVoltage(const double referenceVoltage);

            AnalogSensorBuilder withCalibration(const double* calibration, const unsigned char degree);

            AnalogSensor build(const unsigned char pin, const unsigned int referenceResistor);
    };
}