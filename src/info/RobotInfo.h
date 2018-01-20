/*
 * RobotInfo.h
 * Created: January 9, 2018
 * Author: Kyle
 */
#pragma once

using namespace frc;
namespace frc973{
    //Talons
    static const int LEFT_DRIVE_A_CAN_ID = 2;
    static const int ELEVATOR_CAN_ID = 1;
    static const int LEFT_INTAKE_CAN_ID = 5;
    static const int RIGHT_INTAKE_CAN_ID = 12;
    static const int RIGHT_DRIVE_A_CAN_ID = 14;

    //Victors
    static const int LEFT_DRIVE_B_VICTOR_ID = 2;
    static const int LEFT_DRIVE_C_VICTOR_ID = 3;

    static const int RIGHT_DRIVE_B_VICTOR_ID = 15;
    static const int RIGHT_DRIVE_C_VICTOR_ID = 16;

    //Solenoids

    //Analog

    //Digital
    static const int CUBE_BANNER_SENSOR_DIN = 0;

    //Relays
    static const int COMPRESSOR_RELAY = 0;

    //Joysticks
    static const int DRIVER_JOYSTICK_PORT = 0;
    static const int OPERATOR_JOYSTICK_PORT = 1;
    static const int TUNING_JOYSTICK_PORT = 2;

    //Misc
    static const double DRIVE_WIDTH = 5.0;
};
