#include <catch2/catch.hpp>
#include <ArduinoAdapter.h>
#include <FakeArduino.h>


TEST_CASE("Reads measurements from Arduino sensors") {
    resetPins();

    SECTION("When no data is setup for pin it always returns 0 as reading") {
        REQUIRE(ESP32BBQProbe::readFromNativeSensor(19) == 0);
        REQUIRE(ESP32BBQProbe::readFromNativeSensor(19) == 0);
        REQUIRE(ESP32BBQProbe::readFromNativeSensor(19) == 0);
    };

    SECTION("Pin values are provided") {
        provideDataForAnalogPin(18, 1, 4, 1);
        SECTION("It picks each value from sequence") {
            REQUIRE(ESP32BBQProbe::readFromNativeSensor(18) == 1);
            REQUIRE(ESP32BBQProbe::readFromNativeSensor(18) == 2);
            REQUIRE(ESP32BBQProbe::readFromNativeSensor(18) == 3);
            REQUIRE(ESP32BBQProbe::readFromNativeSensor(18) == 4);
        }

        SECTION("It restarts to original value") {
            ESP32BBQProbe::readFromNativeSensor(18);
            ESP32BBQProbe::readFromNativeSensor(18);
            ESP32BBQProbe::readFromNativeSensor(18);
            REQUIRE(ESP32BBQProbe::readFromNativeSensor(18) == 4);
            REQUIRE(ESP32BBQProbe::readFromNativeSensor(18) == 1);
        }

        SECTION("It offsets pins to 32 base") {
            REQUIRE(ESP32BBQProbe::readFromNativeSensor(18) == 1);
            REQUIRE(ESP32BBQProbe::readFromNativeSensor(50) == 2);
        }
    }
};