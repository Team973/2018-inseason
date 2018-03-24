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
static const double ELEVATOR_INCHES_PER_CLICK = 8.0 / 4096.0;
static const double WRIST_DEGREES_PER_CLICK = 360.0 / 4096.0;
static const double ELEVATOR_SOFT_HEIGHT_LIMIT = 80.5;
static const double ELEVATOR_FEED_FORWARD = 0.10;

// Solenoids
static const int PCM_CAN_ID = 17;
static const int CUBE_CLAMP_PCM_ID = 1;
static const int HANGER_PTO_PCM_ID = 0;
static const int FORK_DEPLOY_PCM_ID = 5;
static const int INTAKE_OPENCLOSE_PCM_ID = 4;

// Wrist
static const int CLAW_LEFT_ROLLER_CAN_ID = 5;
static const int CLAW_RIGHT_ROLLER_CAN_ID = 12;
static const int WRIST_CAN_ID = 7;
static const int WRIST_REVERSE_SOFT_LIMIT = -45.0;
static const int WRIST_FORWARD_SOFT_LIMIT = 90.0;

// Hanger
static const int FORKLIFT_TALON_CAN_ID = 6;

// Digital
static const int INTAKE_BEAM_BREAKER_SENSOR_DIN = 3;
static const int PRESSURE_DIN_ID = 1;

// Relays
static const int COMPRESSOR_RELAY = 0;

// Joysticks
static const int DRIVER_JOYSTICK_PORT = 0;
static const int OPERATOR_JOYSTICK_PORT = 1;

// LEDs
static const int NUM_LED = 26;

// Constants
static const double ROBOT_LOOP_PERIOD_SEC_PER_LOOP = 1.0 / 20.0;
static const double ELEVATOR_MAX_SPEED = 4000.0;
static const double WRIST_MAX_SPEED = 3000.0;

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
