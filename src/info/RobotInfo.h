/*
 * RobotInfo.h
 * Created: January 9, 2018
 * Author: Kyle
 */
#pragma once

#include "lib/util/Util.h"

using namespace frc;

namespace frc973 {
/**
 * Drive Subsystem
 */

// CAN IDs
static const int LEFT_DRIVE_A_CAN_ID = 16;
static const int LEFT_DRIVE_B_VICTOR_ID = 15;
static const int LEFT_DRIVE_C_VICTOR_ID = 14;
static const int RIGHT_DRIVE_A_CAN_ID = 1;
static const int RIGHT_DRIVE_B_VICTOR_ID = 2;
static const int RIGHT_DRIVE_C_VICTOR_ID = 3;

// Constants
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


/**
 * Elevator Subsystem
 */

// CAN IDs
static const int ELEVATOR_CAN_ID = 4;

// Constants
static const double ELEVATOR_INCHES_PER_CLICK = 8.0 / 4096.0;
static const double ELEVATOR_SOFT_HEIGHT_LIMIT = 80.5;
static const double ELEVATOR_FEED_FORWARD = 0.10;
static const double ELEVATOR_MAX_SPEED = 4000.0;


/**
 * Hanger Subsystem
 */

// CAN IDs
static const int FORKLIFT_TALON_CAN_ID = 6;

// Pnuematics
static const int HANGER_PTO_PCM_ID = 0;
static const int FORK_DEPLOY_PCM_ID = 5;


/**
 * Intake Subsystem
 */

// CAN IDs
static const int CLAW_LEFT_ROLLER_CAN_ID = 5;
static const int CLAW_RIGHT_ROLLER_CAN_ID = 12;

// Digital Inputs
static const int RIGHT_INTAKE_BEAM_BREAKER_SENSOR_DIN = 2;
static const int LEFT_INTAKE_BEAM_BREAKER_SENSOR_DIN = 3;

// Pneumatics
static const int CUBE_CLAMP_PCM_ID = 1;


/**
 * Wrist Subsystem
 */

// CAN IDs
static const int WRIST_CAN_ID = 7;

// Constants
static const int WRIST_REVERSE_SOFT_LIMIT = -80.0;
static const int WRIST_FORWARD_SOFT_LIMIT = 90.0;
static const double WRIST_MAX_SPEED = 3000.0;


/**
 * Pneumatics Hardware
 */

// Digital Inputs
static const int PRESSURE_DIN_ID = 1;

// Relays
static const int COMPRESSOR_RELAY = 0;


/**
 * Misc
 */

// Joysticks
static const int DRIVER_JOYSTICK_PORT = 0;
static const int OPERATOR_JOYSTICK_PORT = 1;

// LEDs
static const int NUM_LED = 26;

// Constants
static const double ROBOT_LOOP_PERIOD_SEC_PER_LOOP = 1.0 / 20.0;
