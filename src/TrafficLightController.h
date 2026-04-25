// src/TrafficLightController.h

#pragma once
#include "TrafficLightEvent.h"
#include "TrafficLightState.h"

class TrafficLightController {
    public:
        TrafficLightController();

        void processEvent(TrafficLightEvent event);

        TrafficLightState getState() const;

        int getRemainingTime() const;
    
    private:
        TrafficLightState state;

        void tick(int time);
        void setState(TrafficLightState newState);

        int remainingLightTime;
        int remainingPedestrianTime;

        int redLightTime;
        int yellowLightTime;
        int greenLightTime;
        int pedestrianTime;

        bool pedestrianButtonPressed;
        bool isFault;
};