#include <AnalogSensor.h>
#include <math.h>

using namespace ESP32BBQProbe;

AnalogSensor::AnalogSensor(
    const unsigned char pin,
    const unsigned int resolution,
    const double referenceVoltage,
    const unsigned referenceResistor,
    const double *calibration
) {
    this->pin = pin;
    this->referenceVoltage = referenceVoltage;
    this->referenceResistor = referenceResistor;
    this->resolution = resolution;

    for (int i = 0; i < 7; i ++) {
        this->calibration[i] = calibration[i];
    }
}

int AnalogSensor::readValue() const {
    int value = readFromNativeSensor(pin);

    return (int)nearbyint(
        calibration[0] * pow(value, 6)
            + calibration[1] * pow(value, 5)
            + calibration[2] * pow(value, 4)
            + calibration[3] * pow(value, 3)
            + calibration[4] * pow(value, 2)
            + calibration[5] * pow(value, 1)
            + calibration[6]
    );
}

double AnalogSensor::readVoltage() const {
    return (referenceVoltage / resolution) * this->readValue();
}

int AnalogSensor::readResistance() const {
    double observedVoltage = AnalogSensor::readValue();
    return (int)(observedVoltage * referenceResistor / (resolution - observedVoltage));
}

AnalogSensor AnalogSensorBuilder::build(const unsigned char pin, const unsigned int referenceResistor) {
    AnalogSensor sensor(pin, resolution, referenceVoltage, referenceResistor, calibration);
    return sensor;
}

AnalogSensorBuilder AnalogSensorBuilder::withReferenceVoltage(const double referenceVoltage) {
    this->referenceVoltage = referenceVoltage;
    return *this;
}

AnalogSensorBuilder AnalogSensorBuilder::withCalibration(const double* calibration, const unsigned char degree) {
    int max = degree + 1;
    unsigned int offset = 7 - max;

    for (auto i = 0; i < 7; i ++) {
        if (i < offset) {
            continue;
        }

        this->calibration[i] = calibration[i - offset];
    }

    return *this;
}

AnalogSensorBuilder AnalogSensorBuilder::withResolution(const unsigned int resolution) {
    this->resolution = resolution;
    return *this;
}