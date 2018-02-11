/*
 * RobotInfo.h
 * Created: January 9, 2018
 * Author: Kyle
 */
#pragma once

#include "lib/util/Util.h"

using namespace frc;

namespace frc973 {
// Drive
static const int LEFT_DRIVE_A_CAN_ID = 16;
static const int LEFT_DRIVE_B_VICTOR_ID = 15;
static const int LEFT_DRIVE_C_VICTOR_ID = 14;
static const int RIGHT_DRIVE_A_CAN_ID = 1;
static const int RIGHT_DRIVE_B_VICTOR_ID = 2;
static const int RIGHT_DRIVE_C_VICTOR_ID = 3;

// Elevator
static const int ELEVATOR_CAN_ID = 4;

// Solenoids
static const int PCM_CAN_ID = 17;
static const int CUBE_CLAMP_PCM_ID = 1;
static const int CLAW_KICKER_PCM_ID = 2;
static const int HANGER_PTO_PCM_ID = 0;

// Claw
static const int CLAW_LEFT_ROLLER_CAN_ID = 5;
static const int CLAW_RIGHT_ROLLER_CAN_ID = 12;
static const int CUBE_BANNER_SENSOR_DIN = 0;

// Hanger
static const int FORKLIFT_TALON_CAN_ID = 6;
static const int FORKLIFT_VICTOR_ID = 11;

// Digital
static const int INTAKE_BEAM_BREAKER_SENSOR_DIN = 0;

// Digital
static const int PRESSURE_DIN_ID = 1;

// Relays
static const int COMPRESSOR_RELAY = 0;

// Joysticks
static const int DRIVER_JOYSTICK_PORT = 0;
static const int OPERATOR_JOYSTICK_PORT = 1;
static const int TUNING_JOYSTICK_PORT = 2;

// Drive
static constexpr double DRIVE_WIDTH = 25.205;
static constexpr double DRIVE_WHEEL_DIAMETER = 5.0;
static constexpr double DRIVE_ENCODER_COUNT = 4096;
static constexpr double DRIVE_DIST_PER_REVOLUTION =
    DRIVE_WHEEL_DIAMETER * Constants::PI;
static constexpr double DRIVE_DIST_PER_CLICK =
    DRIVE_DIST_PER_REVOLUTION / DRIVE_ENCODER_COUNT;
static constexpr double DRIVE_IPS_FROM_RPM = DRIVE_DIST_PER_REVOLUTION / 60.0;
static constexpr double DRIVE_IPS_FROM_CPDS =
    1 * 10 / DRIVE_ENCODER_COUNT * DRIVE_DIST_PER_REVOLUTION;  // aka 0.0383
};
