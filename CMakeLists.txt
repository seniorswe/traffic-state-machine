cmake_minimum_required(VERSION 3.16)

project(traffic-state-machine LANGUAGES CXX)

find_package(Threads REQUIRED)

add_library(traffic-controller
    src/Logger.cpp
    src/TrafficLightController.cpp
)

target_include_directories(traffic-controller PUBLIC include)
target_compile_features(traffic-controller PUBLIC cxx_std_17)

add_executable(traffic-state-machine
    src/main.cpp
)

target_link_libraries(traffic-state-machine PRIVATE traffic-controller Threads::Threads)

enable_testing()

add_executable(traffic-controller-tests
    tests/TrafficLightControllerTests.cpp
)

target_link_libraries(traffic-controller-tests PRIVATE traffic-controller)

add_test(NAME traffic-controller-tests COMMAND traffic-controller-tests)
