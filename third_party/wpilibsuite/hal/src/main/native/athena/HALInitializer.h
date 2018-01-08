/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

namespace hal {
namespace init {
extern void InitializeAccelerometer();
extern void InitializeAnalogAccumulator();
extern void InitializeAnalogGyro();
extern void InitializeAnalogInput();
extern void InitializeAnalogInternal();
extern void InitializeAnalogOutput();
extern void InitializeAnalogTrigger();
extern void InitializeCAN();
extern void InitializeCompressor();
extern void InitializeConstants();
extern void InitializeCounter();
extern void InitializeDigitalInternal();
extern void InitializeDIO();
extern void InitializeEncoder();
extern void InitializeFPGAEncoder();
extern void InitializeFRCDriverStation();
extern void InitializeHAL();
extern void InitializeI2C();
extern void InitialzeInterrupts();
extern void InitializeNotifier();
extern void InitializeOSSerialPort();
extern void InitializePCMInternal();
extern void InitializePDP();
extern void InitializePorts();
extern void InitializePower();
extern void InitializePWM();
extern void InitializeRelay();
extern void InitializeSerialPort();
extern void InitializeSolenoid();
extern void InitializeSPI();
extern void InitializeThreads();
extern void InitializeHandlesInternal();
}  // namespace init
}  // namespace hal
