// src/TrafficLightController.cpp

#include "TrafficLightController.h"

TrafficLightController::TrafficLightController()
    :   state(TrafficLightState::RED),
        remainingLightTime(TrafficConstants::RED_TIME),
        redLightTime(TrafficConstants::RED_TIME),
        yellowLightTime(TrafficConstants::YELLOW_TIME),
        greenLightTime(TrafficConstants::GREEN_TIME),
        pedestrianButtonPressed(false),
        isFault(false) {
            setState(TrafficLightState::RED);
        }

int TrafficLightController::getRemainingTime() const {
    return remainingLightTime;
}

TrafficLightState TrafficLightController::getState() const {
    return state;
}

void TrafficLightController::processEvent(TrafficLightEvent event) {
    if (event == TrafficLightEvent::ERROR_ACTIVE) {
        isFault = true;
        setState(TrafficLightState::ERROR);
        return;
    }

    if (event == TrafficLightEvent::ERROR_CLEARED) {
        isFault = false;
        setState(TrafficLightState::RED);
        return;
    }

    if (event == TrafficLightEvent::PEDESTRIAN_BUTTON_PRESSED) {
        if (state == TrafficLightState::GREEN && !pedestrianButtonPressed) {
            tick(TrafficConstants::PEDESTRIAN_REDUCTION);
        }
        pedestrianButtonPressed = true;
        return;
    }

    if (event == TrafficLightEvent::TIMER_EXPIRED) {
        pedestrianButtonPressed = false;
        switch (state) {
            case TrafficLightState::RED:
                setState(TrafficLightState::GREEN);
                break;
            case TrafficLightState::YELLOW:
                setState(TrafficLightState::RED);
                break;
            case TrafficLightState::GREEN:
                setState(TrafficLightState::YELLOW);
                break;
            case TrafficLightState::ERROR:
                break;
        }
    }
}

void TrafficLightController::tick(int time = 0) {
    if (isFault) {
        return;
    }

    remainingLightTime -= time;

    if (remainingLightTime <= 0) {
        processEvent(TrafficLightEvent::TIMER_EXPIRED);
    }
}

void TrafficLightController::setState(TrafficLightState newState) {
    state = newState;

    if (state == TrafficLightState::RED) {
        remainingLightTime = redLightTime;
    } else if (state == TrafficLightState::YELLOW) {
        remainingLightTime = yellowLightTime;
    } else if (state == TrafficLightState::GREEN) {
        remainingLightTime = greenLightTime;
    } else if (state == TrafficLightState::ERROR) {
        remainingLightTime = 0;
    }
}
