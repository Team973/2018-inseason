#include "lib/helpers/PoofsJoystickHelper.h"
#include "lib/managers/TaskMgr.h"
#include "lib/util/Util.h"
#include <string>
#include <stdlib.h>

namespace frc973 {

PoofsJoystick::PoofsJoystick(uint16_t port, TaskMgr *scheduler)
        : Joystick(port)
        , m_port(port)
        , m_prevBtn(0)
        , m_scheduler(scheduler)
        , m_logCell(nullptr) {
    if (scheduler != nullptr) {
        scheduler->RegisterTask("PoofsJoystickHelper", this, TASK_PRE_PERIODIC);
    }
}

PoofsJoystick::~PoofsJoystick() {
    if (m_scheduler != nullptr) {
        m_scheduler->UnregisterTask(this);
    }
}

PoofsJoystick *PoofsJoystick::RegisterLog(LogSpreadsheet *logger) {
    if (m_logCell == nullptr) {
        // TODO this memory is never freed
        char *cellTitleBuf = (char *)malloc(32 * sizeof(char));
        sprintf(cellTitleBuf, "Joystick Btn Port %d", m_port);

        m_logCell = new LogCell(cellTitleBuf, 64);
        logger->RegisterCell(m_logCell);
    }

    return this;
}

double PoofsJoystick::GetLXAxis() {
    return this->GetRawAxis(PoofsJoysticks::LeftXAxis);
}

double PoofsJoystick::GetLYAxis() {
    return this->GetRawAxis(PoofsJoysticks::LeftYAxis);
}

double PoofsJoystick::GetRXAxis() {
    return this->GetRawAxis(PoofsJoysticks::RightXAxis);
}

double PoofsJoystick::GetRYAxis() {
    return this->GetRawAxis(PoofsJoysticks::RightYAxis);
}
/**
 * Careful this code is dense and contains crazy bit-shifty logic.
 *    X&~(X^-X) extracts the least significant set bit from X in mask form
 *    __builtin_ffs(Y) gets the position of the least significant set bit
 */
void PoofsJoystick::TaskPrePeriodic(RobotMode mode) {
}
}
