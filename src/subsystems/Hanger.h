/*
 * Hanger.h
 *
 *  Created on: January 7, 2018
 *      Author: Kyle
 */
#pragma once

#include "WPILib.h"
#include "Phoenix.h"
#include "lib/managers/CoopTask.h"
#include "lib/logging/LogSpreadsheet.h"
#include "src/RobotInfo.h"

using namespace frc;

namespace frc973 {
class TaskMgr;
class LogSpreadsheet;

class Hanger : public CoopTask {
    public:
        Hanger(TaskMgr *scheduler, LogSpreadsheet *logger);
        virtual ~Hanger();

        void TaskPeriodic(RobotMode mode);
    private:
        TaskMgr *m_scheduler;
}
}
