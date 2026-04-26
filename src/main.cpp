// src/main.cpp

#include "Logger.h"
#include "TrafficLightController.h"

int main() {
    Logger logger;
    TrafficLightController trafficController;

    logger.info("Started Traffic Controller!");

    trafficController.tick(60);
    trafficController.processEvent(TrafficLightEvent::PEDESTRIAN_BUTTON_PRESSED);
    trafficController.tick(20);

    return 0;
}