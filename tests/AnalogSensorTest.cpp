#include <catch2/catch.hpp>
#include <AnalogSensor.h>
#include <FakeArduino.h>

using namespace ESP32BBQProbe;

TEST_CASE("Analog Sensor Behaviour") {
    resetPins();

    SECTION("Uncalibrated sensor with default settings") {
        AnalogSensor sensor = ESP32BBQProbe::AnalogSensorBuilder().build(18, 100000);

        SECTION("Returns value from sensor with zero") {
            REQUIRE(sensor.readValue() == 0);
            REQUIRE(sensor.readValue() == 0);
        }

        SECTION("Returns data from native arduino reader") {
            provideDataForAnalogPin(18, 1, 3, 1);
            REQUIRE(sensor.readValue() == 1);
            REQUIRE(sensor.readValue() == 2);
            REQUIRE(sensor.readValue() == 3);
            REQUIRE(sensor.readValue() == 1);
        }

        SECTION("Reads sensor voltage on basis of 3.3 volts and 4095 resolution") {
            provideDataForAnalogPin(18, 0, 4095, 100);
            REQUIRE(sensor.readVoltage() == 0);
            REQUIRE(sensor.readVoltage() == Approx(0.08059).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.16117).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.24176).margin(0.0001));
        }

        SECTION("Reads resistance based on reference value for resistor") {
            provideDataForAnalogPin(18, 0, 4095, 500);
            REQUIRE(sensor.readResistance() == 0);
            REQUIRE(sensor.readResistance() == 13908);
            REQUIRE(sensor.readResistance() == 32310);
        }
    }

    SECTION("Adjusts calculations to different voltage") {
        AnalogSensor sensor = ESP32BBQProbe::AnalogSensorBuilder()
                .withReferenceVoltage(5.0)
                .build(18, 100000);

        SECTION("Reads sensor voltage on basis of 5 volts and 4095 resolution") {
            provideDataForAnalogPin(18, 0, 4095, 100);
            REQUIRE(sensor.readVoltage() == 0);
            REQUIRE(sensor.readVoltage() == Approx(0.12210).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.24420).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.36630).margin(0.0001));
        }

        SECTION("Reads resistance based on reference value for resistor") {
            provideDataForAnalogPin(18, 0, 4095, 500);
            REQUIRE(sensor.readResistance() == 0);
            REQUIRE(sensor.readResistance() == 13908);
            REQUIRE(sensor.readResistance() == 32310);
        }
    }

    SECTION("Adjusts calculations to smaller resolution") {
        AnalogSensor sensor = ESP32BBQProbe::AnalogSensorBuilder()
                .withResolution(1023)
                .build(18, 100000);

        SECTION("Reads sensor voltage on basis of 3.3 volts and 1025 resolution") {
            provideDataForAnalogPin(18, 0, 1025, 100);
            REQUIRE(sensor.readVoltage() == 0);
            REQUIRE(sensor.readVoltage() == Approx(0.32258).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.64516).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.96774).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(1.29032).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(1.61290).margin(0.0001));
        }

        SECTION("Reads resistance based on reference value for resistor") {
            provideDataForAnalogPin(18, 0, 1025, 500);
            REQUIRE(sensor.readResistance() == 0);
            REQUIRE(sensor.readResistance() == 95602);
            REQUIRE(sensor.readResistance() == 4347826);
        }
    }

    SECTION("Calibrates values with 3rd degree polynomial") {
        double calibration[4] = {0.0002, 0.0003, 0.0004, 3};

        AnalogSensor sensor = ESP32BBQProbe::AnalogSensorBuilder()
                .withCalibration(calibration, 3)
                .build(18, 100000);

        provideDataForAnalogPin(18, 0, 400, 50);

        SECTION("Returns data from native Arduino reader") {
            REQUIRE(sensor.readValue() == 3);
            REQUIRE(sensor.readValue() == 29);
            REQUIRE(sensor.readValue() == 206);
            REQUIRE(sensor.readValue() == 685);
        }

        SECTION("Reads resistance based on reference value for resistor") {
            REQUIRE(sensor.readResistance() == 73);
            REQUIRE(sensor.readResistance() == 713);
            REQUIRE(sensor.readResistance() == 5296);
        }

        SECTION("Reads sensor voltage on basis of 3.3 volts and 4095 resolution") {
            REQUIRE(sensor.readVoltage() == Approx(0.0024).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.0233).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.1660).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.5520).margin(0.0001));
        }
    }

    SECTION("Calibrates values with 6th degree polynomial") {
        double calibration[7] = {0, 0, 0, 0.0002, 0.0003, 0.0004, 3};

        AnalogSensor sensor = ESP32BBQProbe::AnalogSensorBuilder()
                .withCalibration(calibration, 6)
                .build(18, 100000);

        provideDataForAnalogPin(18, 0, 400, 50);

        SECTION("Returns data from native Arduino reader") {
            REQUIRE(sensor.readValue() == 3);
            REQUIRE(sensor.readValue() == 29);
            REQUIRE(sensor.readValue() == 206);
            REQUIRE(sensor.readValue() == 685);
        }

        SECTION("Reads resistance based on reference value for resistor") {
            REQUIRE(sensor.readResistance() == 73);
            REQUIRE(sensor.readResistance() == 713);
            REQUIRE(sensor.readResistance() == 5296);
        }

        SECTION("Reads sensor voltage on basis of 3.3 volts and 4095 resolution") {
            REQUIRE(sensor.readVoltage() == Approx(0.0024).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.0233).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.1660).margin(0.0001));
            REQUIRE(sensor.readVoltage() == Approx(0.5520).margin(0.0001));
        }
    }

    SECTION("Restricts calibration to 3rd from 6th degree polynomials") {

    }
}