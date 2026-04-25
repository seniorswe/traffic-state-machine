// src/TrafficLightController.h

#include "TrafficLightController.h"

TrafficLightController::TrafficLightController()
    :   state(TrafficLightState::RED),
        remainingLightTime(0),
        remainingPedestrianTime(0),
        redLightTime(60),
        yellowLightTime(5),
        greenLightTime(120),
        pedestrianTime(20),
        pedestrianButtonPressed(false),
        isFault(false) {
            setState(TrafficLightState::RED);
        }

// Public Methods

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
            tick(30);
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

// Private Methods

void TrafficLightController::setState(TrafficLightState newState) {
    state = newState;

    if (state == TrafficLightState::RED) {
        remainingPedestrianTime = pedestrianTime;
        remainingLightTime = redLightTime;
    } else if (state == TrafficLightState::YELLOW) {
        remainingLightTime = yellowLightTime;
    } else if (state == TrafficLightState::GREEN) {
        remainingLightTime = greenLightTime;
    } else if (state == TrafficLightState::ERROR) {
        remainingLightTime = 0;
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

    if (pedestrianTime > 0) {
        remainingPedestrianTime -= time;
    }
}
