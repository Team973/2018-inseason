#include "lib/helpers/PoofsJoystickHelper.h"
#include "lib/managers/TaskMgr.h"
#include "lib/util/Util.h"
#include <string>
#include <stdlib.h>

namespace frc973 {

ObservablePoofsJoystick::ObservablePoofsJoystick(
    uint16_t port, PoofsJoystickObserver *observer, TaskMgr *scheduler,
    DriverStation *ds)
        : Joystick(port)
        , m_port(port)
        , m_observer(observer)
        , m_ds(ds)
        , m_prevBtn(0)
        , m_scheduler(scheduler)
        , m_logCell(nullptr)
        , m_lastLTrigger(false)
        , m_lastLBumper(false)
        , m_lastRTrigger(false)
        , m_lastRBumper(false) {
    if (m_ds == nullptr) {
        m_ds = &DriverStation::GetInstance();
    }

    m_prevBtn = m_ds->GetStickButtons(port);

    if (scheduler != nullptr) {
        scheduler->RegisterTask("JoystickHelper", this, TASK_PRE_PERIODIC);
    }
}

ObservablePoofsJoystick::~ObservablePoofsJoystick() {
    if (m_scheduler != nullptr) {
        m_scheduler->UnregisterTask(this);
    }
}

ObservablePoofsJoystick *ObservablePoofsJoystick::RegisterLog(
    LogSpreadsheet *logger) {
    if (m_logCell == nullptr) {
        // TODO this memory is never freed
        char *cellTitleBuf = (char *)malloc(32 * sizeof(char));
        sprintf(cellTitleBuf, "Joystick Btn Port %d", m_port);

        m_logCell = new LogCell(cellTitleBuf, 64);
        logger->RegisterCell(m_logCell);
    }

    return this;
}

float ObservablePoofsJoystick::GetRawAxisWithDeadband(int axis, bool fSquared,
                                                      double threshold) {
    float value = Util::deadband(GetRawAxis(axis), threshold);

    if (fSquared) {
        value = Util::signSquare(value);
    }

    return value;
}

bool ObservablePoofsJoystick::GetLTrigger() {
    if (this->GetRawButton(PoofsJoysticks::LeftTrigger)) {
        m_lastLTrigger = true;
    }
    else {
        m_lastLTrigger = false;
    }

    return m_lastLTrigger;
}

bool ObservablePoofsJoystick::GetLBumper() {
    if (this->GetRawButton(PoofsJoysticks::LeftBumper)) {
        m_lastLBumper = true;
    }
    else {
        m_lastLBumper = false;
    }

    return m_lastLBumper;
}

bool ObservablePoofsJoystick::GetRTrigger() {
    if (this->GetRawButton(PoofsJoysticks::RightTrigger)) {
        m_lastRTrigger = true;
    }
    else {
        m_lastRTrigger = false;
    }

    return m_lastRTrigger;
}

bool ObservablePoofsJoystick::GetRBumper() {
    if (this->GetRawButton(PoofsJoysticks::RightBumper)) {
        m_lastRBumper = true;
    }
    else {
        m_lastRBumper = false;
    }

    return m_lastRBumper;
}

uint32_t ObservablePoofsJoystick::GetAllButtons() {
    uint32_t btns = m_ds->GetStickButtons(m_port);

    btns |= GetLTrigger() << (PoofsJoysticks::LeftTrigger - 1);
    btns |= GetLBumper() << (PoofsJoysticks::LeftBumper - 1);
    btns |= GetRTrigger() << (PoofsJoysticks::RightTrigger - 1);
    btns |= GetRBumper() << (PoofsJoysticks::RightBumper - 1);

    return btns;
}

/**
 * Careful this code is dense and contains crazy bit-shifty logic.
 *    X&~(X^-X) extracts the least significant set bit from X in mask form
 *    __builtin_ffs(Y) gets the position of the least significant set bit
 */
void ObservablePoofsJoystick::TaskPrePeriodic(RobotMode mode) {
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
                m_observer->ObservePoofsJoystickStateChange(m_port, btn, true);
            }
            else {
                /* Button is released */
                m_observer->ObservePoofsJoystickStateChange(m_port, btn, false);
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
