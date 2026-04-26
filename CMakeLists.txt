cmake_minimum_required(VERSION 3.16)

project(traffic-state-machine LANGUAGES CXX)

add_executable(traffic-state-machine
    src/main.cpp
    src/Logger.cpp
    src/TrafficLightController.cpp
)

target_include_directories(traffic-state-machine PRIVATE include)

target_compile_features(traffic-state-machine PRIVATE cxx_std_17)
