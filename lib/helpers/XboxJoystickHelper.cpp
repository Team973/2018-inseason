#include "lib/helpers/XboxJoystickHelper.h"
#include "lib/managers/TaskMgr.h"
#include "lib/util/Util.h"
#include <string>
#include <stdlib.h>

namespace frc973 {

XboxJoystick::XboxJoystick(uint16_t port, JoystickHelperBase *observer,
                           TaskMgr *scheduler, DriverStation *ds)
        : Joystick(port)
        , m_port(port)
        , m_observer(observer)
        , m_ds(ds)
        , m_prevBtn(0)
        , m_scheduler(scheduler)
        , m_logCell(nullptr) {
    if (m_ds == nullptr) {
        m_ds = &DriverStation::GetInstance();
    }

    m_prevBtn = m_ds->GetStickButtons(port);

    if (scheduler != nullptr) {
        scheduler->RegisterTask("XboxJoystickHelper", this, TASK_PRE_PERIODIC);
    }
}

XboxJoystick::~XboxJoystick() {
    if (m_scheduler != nullptr) {
        m_scheduler->UnregisterTask(this);
    }
}

XboxJoystick *XboxJoystick::RegisterLog(LogSpreadsheet *logger) {
    if (m_logCell == nullptr) {
        // TODO this memory is never freed
        char *cellTitleBuf = (char *)malloc(32 * sizeof(char));
        sprintf(cellTitleBuf, "Joystick Btn Port %d", m_port);

        m_logCell = new LogCell(cellTitleBuf, 64);
        logger->RegisterCell(m_logCell);
    }

    return this;
}

/**
 * Careful this code is dense and contains crazy bit-shifty logic.
 *    X&~(X^-X) extracts the least significant set bit from X in mask form
 *    __builtin_ffs(Y) gets the position of the least significant set bit
 */
void XboxJoystick::TaskPrePeriodic(RobotMode mode) {
}
}
