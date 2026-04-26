// src/main.cpp

#include "Logger.h"
#include "TrafficLightController.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>

void getUserInput(std::atomic<bool>& stopProgram, std::atomic<bool>& pedestrianButtonPressed) {
    while (!stopProgram.load()) {
        int userInput;

        std::cout << "-------------------------------------------- \n";
        std::cout << "Enter 0 to stop the system. \n";
        std::cout << "Enter 1 for pedestrian crosswalk. \n";
        std::cout << "-------------------------------------------- \n";
        std::cout << "Logs are live, input is expected below.. \n";
        std::cout << "-------------------------------------------- \n";
        
        

        if (!(std::cin >> userInput)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch(userInput) {
            case (0):
                stopProgram.store(true);
                break;
            case(1):
                pedestrianButtonPressed.store(true);
                break;
        }
    }
}

int main() {
    Logger logger;
    TrafficLightController trafficController;

    std::atomic<bool> stopProgram{false};
    std::atomic<bool> pedestrianButtonPressed{false};

    std::thread inputThread(
        getUserInput,
        std::ref(stopProgram),
        std::ref(pedestrianButtonPressed)
    );

    logger.info("Started Traffic Controller!");

    while (!stopProgram.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        trafficController.tick(1);

        if (pedestrianButtonPressed.exchange(false)) {
            logger.info("INFO | Pedestrian button manually triggered");
            trafficController.processEvent(TrafficLightEvent::PEDESTRIAN_BUTTON_PRESSED);
        }
    }

    if (inputThread.joinable()) {
        inputThread.join();
    }

    logger.info("INFO | Traffic Controller Stopped!");
}
