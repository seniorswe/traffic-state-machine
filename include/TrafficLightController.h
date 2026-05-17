// src/TrafficLightController.h

#pragma once
#include "TrafficLightEvent.h"
#include "TrafficLightState.h"

#include <string>

namespace TrafficConstants {
    constexpr int RED_TIME = 60;
    constexpr int YELLOW_TIME = 5;
    constexpr int GREEN_TIME = 120;
    constexpr int PEDESTRIAN_REDUCTION = 30;
}

class TrafficLightController {
    public:
        TrafficLightController();

        TrafficLightState getState() const;

        void processEvent(TrafficLightEvent event);
        void tick(int time);

        int getRemainingTime() const;
        std::string getTimeStatus() const;
    
    private:
        TrafficLightState state;
        void setState(TrafficLightState newState);
        std::string stateToString(TrafficLightState currentState) const;

        int remainingLightTime;
        int redLightTime;
        int yellowLightTime;
        int greenLightTime;

        bool pedestrianButtonPressed;
        bool isFault;
};
