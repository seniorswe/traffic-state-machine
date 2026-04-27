// src/main.cpp

#include "Logger.h"
#include "TrafficLightController.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <limits>

void getUserInput(std::atomic<bool>& stopProgram, std::atomic<bool>& getTimeStatus, std::atomic<bool>& pedestrianRequestPending) {
    while (!stopProgram.load()) {
        int input;
        
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch(input) {
            case (0):
                stopProgram.store(true);
                break;
            case(1):
                getTimeStatus.store(true);
                break;
            case(2):
                pedestrianRequestPending.store(true);
                break;
        }
    }
}

int main() {
    Logger logger;
    TrafficLightController trafficController;

    std::atomic<bool> stopProgram{false};
    std::atomic<bool> getTimeStatus{false};
    std::atomic<bool> pedestrianRequestPending{false};

    std::thread inputThread(
        getUserInput,
        std::ref(stopProgram),
        std::ref(getTimeStatus),
        std::ref(pedestrianRequestPending)
    );

    logger.info(
        "Started Traffic Controller! \n"
        "-------------------------------------------- \n"
        "Enter 0 to stop the system \n"
        "Enter 1 for current state and time remaining. \n"
        "Enter 2 for pedestrian crosswalk. \n"
        "-------------------------------------------- \n"
        "Logs are live, input is expected below.. \n"
        "--------------------------------------------"
    );

    while (!stopProgram.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        trafficController.tick(1);

        if (getTimeStatus.exchange(false)) {
            logger.info(trafficController.getTimeStatus());
        }

        if (pedestrianRequestPending.exchange(false)) {
            logger.info("INFO | Pedestrian button manually triggered");
            trafficController.processEvent(TrafficLightEvent::PEDESTRIAN_BUTTON_PRESSED);
        }
    }

    if (inputThread.joinable()) {
        inputThread.join();
    }

    logger.info("INFO | Traffic Controller Stopped!");
}
