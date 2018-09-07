#include "lib/helpers/PoofsJoystickHelper.h"
#include "lib/managers/TaskMgr.h"
#include "lib/util/Util.h"
#include <string>
#include <stdlib.h>

namespace frc973 {

ObservableJoystick::ObservableJoystick(uint16_t port,
                                       JoystickObserver *observer,
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

ObservableJoystick::~ObservableJoystick() {
    if (m_scheduler != nullptr) {
        m_scheduler->UnregisterTask(this);
    }
}

ObservableJoystick *ObservableJoystick::RegisterLog(LogSpreadsheet *logger) {
    if (m_logCell == nullptr) {
        // TODO this memory is never freed
        char *cellTitleBuf = (char *)malloc(32 * sizeof(char));
        sprintf(cellTitleBuf, "Joystick Btn Port %d", m_port);

        m_logCell = new LogCell(cellTitleBuf, 64);
        logger->RegisterCell(m_logCell);
    }

    return this;
}

float ObservableJoystick::GetRawAxisWithDeadband(int axis, bool fSquared,
                                                 double threshold) {
    float value = Util::deadband(GetRawAxis(axis), threshold);

    if (fSquared) {
        value = Util::signSquare(value);
    }

    return value;
}

bool ObservableJoystick::GetLXVirtButton() {
    double pos = this->GetRawAxis(PoofsJoysticks::LeftXAxis);

    if (pos > VIRTUAL_JOYSTICK_THRESHOLD) {
        m_lastLXVal = true;
    }
    else if (pos < -VIRTUAL_JOYSTICK_THRESHOLD) {
        m_lastLXVal = false;
    }

    return m_lastLXVal;
}

bool ObservableJoystick::GetRXVirtButton() {
    double pos = this->GetRawAxis(PoofsJoysticks::RightXAxis);

    if (pos > VIRTUAL_JOYSTICK_THRESHOLD) {
        m_lastRXVal = true;
    }
    else if (pos < -VIRTUAL_JOYSTICK_THRESHOLD) {
        m_lastRXVal = false;
    }

    return m_lastRXVal;
}

bool ObservableJoystick::GetRYVirtButton() {
    double pos = -this->GetRawAxis(PoofsJoysticks::RightYAxis);

    if (pos > VIRTUAL_JOYSTICK_THRESHOLD) {
        m_lastRYVal = true;
    }
    else if (pos < -VIRTUAL_JOYSTICK_THRESHOLD) {
        m_lastRYVal = false;
    }

    return m_lastRYVal;
}

uint32_t ObservableJoystick::GetAllButtons() {
    uint32_t btns = m_ds->GetStickButtons(m_port);

    btns |= GetLXVirtButton() << (PoofsJoysticks::LeftXAxis - 1);
    btns |= GetLYVirtButton() << (PoofsJoysticks::LeftYAxis - 1);
    btns |= GetRXVirtButton() << (PoofsJoysticks::RightXAxis - 1);
    btns |= GetRYVirtButton() << (PoofsJoysticks::RightYAxis - 1);

    return btns;
}

/**
 * Careful this code is dense and contains crazy bit-shifty logic.
 *    X&~(X^-X) extracts the least significant set bit from X in mask form
 *    __builtin_ffs(Y) gets the position of the least significant set bit
 */
void ObservableJoystick::TaskPrePeriodic(RobotMode mode) {
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
