// src/main.cpp

#include "Logger.h"
#include "TrafficLightController.h"
#include <iostream>

int main() {
    Logger logger;
    TrafficLightController trafficController;

    logger.info("Started Traffic Controller!");

    while (true) {
        int userInput;

        std::cout << "Enter 1 for pedestrian crosswalk. \n";
        std::cout << "Enter 1 for pedestrian crosswalk. \n";
        std::cout << "Input: ";
        
        std::cin >> userInput;

        switch(userInput) {
            case (0):
                logger.info("INFO | Traffic Controller Stopped!");
                return 0;
            case(1):
                logger.info("INFO | Pedestrian button manually triggered");
                trafficController.processEvent(TrafficLightEvent::PEDESTRIAN_BUTTON_PRESSED);
        }
    }
}
