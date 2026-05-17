#include "TrafficLightController.h"

#include <iostream>

int failedTests = 0;

void fail(const char *message) {
  std::cout << "FAILED | " << message << "\n";
  failedTests++;
}

void testStartsAtRed() {
  TrafficLightController trafficController;

  if (trafficController.getState() != TrafficLightState::RED) {
    fail("traffic light should start red");
  }

  if (trafficController.getRemainingTime() != TrafficConstants::RED_TIME) {
    fail("red light should start with full time");
  }
}

void testNormalLightCycle() {
  TrafficLightController trafficController;

  trafficController.tick(TrafficConstants::RED_TIME);
  if (trafficController.getState() != TrafficLightState::GREEN) {
    fail("red should turn green after timer expires");
  }

  trafficController.tick(TrafficConstants::GREEN_TIME);
  if (trafficController.getState() != TrafficLightState::YELLOW) {
    fail("green should turn yellow after timer expires");
  }

  trafficController.tick(TrafficConstants::YELLOW_TIME);
  if (trafficController.getState() != TrafficLightState::RED) {
    fail("yellow should turn red after timer expires");
  }
}

void testPedestrianButton() {
  TrafficLightController trafficController;

  trafficController.tick(TrafficConstants::RED_TIME);
  trafficController.processEvent(TrafficLightEvent::PEDESTRIAN_BUTTON_PRESSED);

  if (trafficController.getRemainingTime() !=
      TrafficConstants::GREEN_TIME - TrafficConstants::PEDESTRIAN_REDUCTION) {
    fail("pedestrian button should reduce green time");
  }

  trafficController.processEvent(TrafficLightEvent::PEDESTRIAN_BUTTON_PRESSED);
  if (trafficController.getRemainingTime() !=
      TrafficConstants::GREEN_TIME - TrafficConstants::PEDESTRIAN_REDUCTION) {
    fail("pedestrian button should not reduce green twice");
  }
}

void testEmergencyOverride() {
  TrafficLightController trafficController;

  trafficController.processEvent(TrafficLightEvent::EMERGENCY_VEHICLE_OVERRIDE);
  if (trafficController.getState() != TrafficLightState::GREEN) {
    fail("emergency override should change red to green");
  }

  trafficController.tick(30);
  trafficController.processEvent(TrafficLightEvent::EMERGENCY_VEHICLE_OVERRIDE);
  if (trafficController.getRemainingTime() != TrafficConstants::GREEN_TIME) {
    fail("emergency override should reset green time");
  }

  trafficController.tick(TrafficConstants::GREEN_TIME);
  if (trafficController.getState() != TrafficLightState::YELLOW) {
    fail("state should be yellow after green expires");
  }

  trafficController.processEvent(TrafficLightEvent::EMERGENCY_VEHICLE_OVERRIDE);
  if (trafficController.getState() != TrafficLightState::GREEN) {
    fail("emergency override should change yellow to green");
  }
}

void testErrorState() {
  TrafficLightController trafficController;

  trafficController.processEvent(TrafficLightEvent::ERROR_ACTIVE);
  if (trafficController.getState() != TrafficLightState::ERROR) {
    fail("error event should set error state");
  }

  trafficController.tick(10);
  if (trafficController.getState() != TrafficLightState::ERROR) {
    fail("timer should not leave error state");
  }

  trafficController.processEvent(TrafficLightEvent::ERROR_CLEARED);
  if (trafficController.getState() != TrafficLightState::RED) {
    fail("clearing error should return to red");
  }
}

int main() {
  testStartsAtRed();
  testNormalLightCycle();
  testPedestrianButton();
  testEmergencyOverride();
  testErrorState();

  if (failedTests > 0) {
    std::cout << failedTests << " tests failed\n";
    return 1;
  }

  std::cout << "All tests passed\n";
  return 0;
}
