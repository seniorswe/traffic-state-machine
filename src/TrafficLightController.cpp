// src/TrafficLightController.cpp

#include "Logger.h"
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

std::string TrafficLightController::getTimeStatus() const {
    return "State: " + stateToString(state) +
        " | Time remaining: " + std::to_string(remainingLightTime) + "s";
}

void TrafficLightController::processEvent(TrafficLightEvent event) {
    Logger logger;

    if (event == TrafficLightEvent::ERROR_ACTIVE) {
        logger.error("Event error");
        isFault = true;
        setState(TrafficLightState::ERROR);
        return;
    }

    if (event == TrafficLightEvent::ERROR_CLEARED) {
        logger.info("Event error cleared");
        isFault = false;
        setState(TrafficLightState::RED);
        return;
    }

    if (event == TrafficLightEvent::PEDESTRIAN_BUTTON_PRESSED) {
        if (state == TrafficLightState::GREEN && !pedestrianButtonPressed) {
            tick(TrafficConstants::PEDESTRIAN_REDUCTION);
            logger.info("Pedestrian time reduction triggered");
        }
        pedestrianButtonPressed = true;
        return;
    }

    if (event == TrafficLightEvent::EMERGENCY_VEHICLE_OVERRIDE) {
        if (state == TrafficLightState::GREEN) {
            logger.info("Override green light increased to 100%");
            setState(TrafficLightState::GREEN);
        } else if (state == TrafficLightState::RED) {
            logger.info("Override green light transition");
            setState(TrafficLightState::GREEN);
        } else if (state == TrafficLightState::YELLOW) {
            logger.info("Override green light transition from yellow");
            setState(TrafficLightState::GREEN);
        }
    }

    if (event == TrafficLightEvent::TIMER_EXPIRED) {
        switch (state) {
            case TrafficLightState::RED:
                logger.info("Red to green light transition");
                setState(TrafficLightState::GREEN);
                break;
            case TrafficLightState::YELLOW:
                logger.info("Yellow to red light transition");
                if (pedestrianButtonPressed) {
                    logger.info("Walk sign active");
                    pedestrianButtonPressed = false;
                }
                setState(TrafficLightState::RED);
                break;
            case TrafficLightState::GREEN:
                logger.info("Green to yellow light transition");
                setState(TrafficLightState::YELLOW);
                break;
            case TrafficLightState::ERROR:
                logger.error("Traffic light has entered an error state");
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

std::string TrafficLightController::stateToString(TrafficLightState state) const {
    switch (state) {
        case TrafficLightState::RED:
            return "RED";
        case TrafficLightState::YELLOW:
            return "YELLOW";
        case TrafficLightState::GREEN:
            return "GREEN";
        case TrafficLightState::ERROR:
            return "ERROR";
    }

    return "UNKNOWN";
}
