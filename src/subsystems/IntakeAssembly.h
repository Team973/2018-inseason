#pragma once

#include "WPILib.h"
#include "ctre/Phoenix.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "src/info/RobotInfo.h"
#include "lib/helpers/JoystickHelper.h"
#include "lib/util/Util.h"
#include "src/subsystems/Elevator.h"
#include "src/subsystems/Wrist.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class IntakeAssembly : public CoopTask {
public:
    IntakeAssembly(TaskMgr *scheduler, LogSpreadsheet *logger,
                   Elevator *elevator, Wrist *wrist);
    virtual ~IntakeAssembly();

    /**
     * Update function synonymous to TeleopContinuous that gets called
     *continuously
     **/
    void TaskPeriodic(RobotMode mode);

private:
    TaskMgr *m_scheduler;

    Elevator *m_elevator;
    Wrist *m_wrist;
};
}
