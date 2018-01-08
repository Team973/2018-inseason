/*----------------------------------------------------------------------------*/
/* Copyright (c) 2011-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Buttons/Button.h"
#include "Buttons/CancelButtonScheduler.h"
#include "Buttons/HeldButtonScheduler.h"
#include "Buttons/PressedButtonScheduler.h"
#include "Buttons/ReleasedButtonScheduler.h"
#include "Buttons/ToggleButtonScheduler.h"
#include "SmartDashboard/SendableBuilder.h"

using namespace frc;

bool Trigger::Grab() { return Get() || m_sendablePressed; }

void Trigger::WhenActive(Command* command) {
  auto pbs = new PressedButtonScheduler(Grab(), this, command);
  pbs->Start();
}

void Trigger::WhileActive(Command* command) {
  auto hbs = new HeldButtonScheduler(Grab(), this, command);
  hbs->Start();
}

void Trigger::WhenInactive(Command* command) {
  auto rbs = new ReleasedButtonScheduler(Grab(), this, command);
  rbs->Start();
}

void Trigger::CancelWhenActive(Command* command) {
  auto cbs = new CancelButtonScheduler(Grab(), this, command);
  cbs->Start();
}

void Trigger::ToggleWhenActive(Command* command) {
  auto tbs = new ToggleButtonScheduler(Grab(), this, command);
  tbs->Start();
}

void Trigger::InitSendable(SendableBuilder& builder) {
  builder.SetSmartDashboardType("Button");
  builder.SetSafeState([=]() { m_sendablePressed = false; });
  builder.AddBooleanProperty("pressed", [=]() { return Grab(); },
                             [=](bool value) { m_sendablePressed = value; });
}
