cmake_minimum_required(VERSION 3.13)
project(ESP32BBQProbe LANGUAGES CXX VERSION 0.0.1)
add_compile_definitions(TEST_HARNESS)
file(GLOB_RECURSE SOURCE RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
file(GLOB_RECURSE UNIT_TESTS RELATIVE ${CMAKE_SOURCE_DIR} "tests/*.cpp")

add_library(ESP32BBQProbe ESP32BBQProbe.h ${SOURCE})
target_include_directories(ESP32BBQProbe
    PUBLIC src
)

find_package(Catch2 REQUIRED)

add_executable(unit_tests ${UNIT_TESTS})
target_link_libraries(unit_tests Catch2::Catch2 ESP32BBQProbe)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests TEST_SUFFIX Test)

# Load and use the .cmake file provided by Catch so all the test cases
# are made available to CTest.
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(unit_tests)

install(
    TARGETS unit_tests
    RUNTIME DESTINATION bin
)
