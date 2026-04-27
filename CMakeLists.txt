cmake_minimum_required(VERSION 3.16)

project(traffic-state-machine LANGUAGES CXX)

find_package(Threads REQUIRED)

add_executable(traffic-state-machine
    src/main.cpp
    src/Logger.cpp
    src/TrafficLightController.cpp
)

target_include_directories(traffic-state-machine PRIVATE include)

target_compile_features(traffic-state-machine PRIVATE cxx_std_17)
target_link_libraries(traffic-state-machine PRIVATE Threads::Threads)