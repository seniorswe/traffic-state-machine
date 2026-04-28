// src/TrafficLightEvent.h

#pragma once

enum class TrafficLightEvent {
  TIMER_EXPIRED,
  ERROR_ACTIVE,
  ERROR_CLEARED,
  PEDESTRIAN_BUTTON_PRESSED,
  EMERGENCY_VEHICLE_OVERRIDE
};