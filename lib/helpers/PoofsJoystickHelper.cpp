#include "lib/helpers/PoofsJoystickHelper.h"
#include "lib/managers/TaskMgr.h"
#include "lib/util/Util.h"
#include <string>
#include <stdlib.h>

namespace frc973 {

PoofsJoystick::PoofsJoystick(uint16_t port, JoystickObserver *observer,
                             TaskMgr *scheduler, DriverStation *ds)
        : Joystick(port)
        , m_port(port)
        , m_observer(observer)
        , m_ds(ds)
        , m_prevBtn(0)
        , m_scheduler(scheduler)
        , m_logCell(nullptr)
        , m_lastLXVal(false)
        , m_lastLYVal(false)
        , m_lastRXVal(false)
        , m_lastRYVal(false) {
    if (m_ds == nullptr) {
        m_ds = &DriverStation::GetInstance();
    }

    m_prevBtn = m_ds->GetStickButtons(port);

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

float PoofsJoystick::GetRawAxisWithDeadband(int axis, bool fSquared,
                                            double threshold) {
    float value = Util::deadband(GetRawAxis(axis), threshold);

    if (fSquared) {
        value = Util::signSquare(value);
    }

    return value;
}

double PoofsJoystick::GetLXAxis() {
    double pos = this->GetRawAxis(PoofsJoysticks::LeftXAxis);
    return pos;
}

double PoofsJoystick::GetLYAxis() {
    double pos = this->GetRawAxis(PoofsJoysticks::LeftYAxis);
    return pos;
}

double PoofsJoystick::GetRXAxis() {
    double pos = this->GetRawAxis(PoofsJoysticks::RightXAxis);
    return pos;
}

double PoofsJoystick::GetRYAxis() {
    double pos = this->GetRawAxis(PoofsJoysticks::RightYAxis);
    return pos;
}
/**
 * Careful this code is dense and contains crazy bit-shifty logic.
 *    X&~(X^-X) extracts the least significant set bit from X in mask form
 *    __builtin_ffs(Y) gets the position of the least significant set bit
 */
void PoofsJoystick::TaskPrePeriodic(RobotMode mode) {
    uint32_t currBtn = GetAllButtons();

    if (m_observer != nullptr) {
        uint32_t changedBtn = m_prevBtn ^ currBtn;
        uint32_t btnMask, btn;

        while (changedBtn != 0) {
            /* btnMask contains the least significant set bit in changedBtn */
            btnMask = changedBtn & ~(changedBtn ^ -changedBtn);
            /* btn contains the index of the lssb in btnMask... aka the button
             * number */
            btn = __builtin_ffs(btnMask);
            if ((currBtn & btnMask) != 0) {
                /* Button is pressed */
                m_observer->ObserveJoystickStateChange(m_port, btn, true);
            }
            else {
                /* Button is released */
                m_observer->ObserveJoystickStateChange(m_port, btn, false);
            }
            /* clear |changedBtn| from the mask so we can get the next lsb */
            changedBtn &= ~btnMask;
        }
    }
    m_prevBtn = currBtn;

    if (m_logCell) {
        m_logCell->LogPrintf("%x", currBtn);
    }
}
}
