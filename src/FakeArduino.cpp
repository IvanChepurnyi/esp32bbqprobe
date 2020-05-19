#include <FakeArduino.h>

class AnalogValueProvider
{
    int minValue;
    int maxValue;
    int incrementStep;
    int currentValue;

    public:
        AnalogValueProvider(int minValue, int maxValue, int incrementStep): AnalogValueProvider() {
            this->minValue = minValue;
            this->maxValue = maxValue;
            this->incrementStep = incrementStep;
            this->currentValue = minValue;
        }

        AnalogValueProvider() {
            minValue = 0;
            maxValue = 0;
            incrementStep = 0;
            currentValue = minValue;
        }

        int value()
        {
            int result = currentValue;
            currentValue += incrementStep;
            if (currentValue > maxValue) {
                currentValue = minValue;
            }

            return result;
        }
};

AnalogValueProvider pinValueProviders[31];

int adjustPin(const unsigned char pin) {
    if (pin > 32) {
        return pin % 32;
    }
    return pin;
}

int analogRead(const unsigned char pin)
{
    return pinValueProviders[adjustPin(pin)-1].value();
}

void provideDataForAnalogPin(unsigned char pin, int min, int max, int step)
{
    pinValueProviders[adjustPin(pin)-1] = AnalogValueProvider(min, max, step);
}

void resetPins() {
    for (auto i = 0; i < 32; i ++) {
        pinValueProviders[i] = AnalogValueProvider();
    }
}