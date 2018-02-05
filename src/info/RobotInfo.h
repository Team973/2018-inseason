/*
 * RobotInfo.h
 * Created: January 9, 2018
 * Author: Kyle
 */
#pragma once

using namespace frc;

namespace frc973 {
// Drive
static const int LEFT_DRIVE_A_CAN_ID = 1;
static const int LEFT_DRIVE_B_VICTOR_ID = 2;
static const int LEFT_DRIVE_C_VICTOR_ID = 3;
static const int RIGHT_DRIVE_A_CAN_ID = 16;
static const int RIGHT_DRIVE_B_VICTOR_ID = 15;
static const int RIGHT_DRIVE_C_VICTOR_ID = 14;

// Elevator
static const int ELEVATOR_CAN_ID = 4;

// Solenoids
static const int CLAW_ARMS_PCM_ID = 2;
static const int CLAW_KICKER_PCM_ID = 3;
static const int KICKER_PIN_PCM_ID = 4;
static const int HANGER_PTO_PCM_ID = 1;

// Claw
static const int CLAW_LEFT_ROLLER_CAN_ID = 5;
static const int CLAW_RIGHT_ROLLER_CAN_ID = 12;
static const int CUBE_BANNER_SENSOR_DIN = 0;

// Hanger
static const int FORKLIFT_TALON_CAN_ID = 6;
static const int FORKLIFT_VICTOR_ID = 11;

// Digital
static const int BEAM_BREAKER_SENSOR_DIN = 0;

// Analog
static const int PRESSURE_ANLG_ID = 0;

// Relays
static const int COMPRESSOR_RELAY = 0;

// Joysticks
static const int DRIVER_JOYSTICK_PORT = 0;
static const int OPERATOR_JOYSTICK_PORT = 1;
static const int TUNING_JOYSTICK_PORT = 2;

// Misc
static const double DRIVE_WIDTH = 5.0;
};
