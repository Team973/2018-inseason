#include "src/AutonomousMode.h"
#include "src/auto/NoAuto.h"
#include "src/auto/ForwardAuto.h"
#include "src/DisabledMode.h"
#include "src/Robot.h"

using namespace frc;

namespace frc973 {
Autonomous::Autonomous(Disabled *disabled)
        : m_noAuto(new NoAuto())
        , m_forwardAuto(new ForwardAuto())
        , m_disabled(disabled)
        , m_randomMessage("")
        , m_switchScalePosition(SwitchScalePosition::LL) {
}

Autonomous::~Autonomous() {
}

void Autonomous::AutonomousInit() {
    // Remember to zero all sensors here
    std::cout << "Autonomous Start" << std::endl;

    m_randomMessage = DriverStation::GetInstance().GetGameSpecificMessage();
    DBStringPrintf(DB_LINE1, "%s", m_randomMessage.c_str());

    if (m_randomMessage[0] == 'L' && m_randomMessage[1] == 'L') {
        m_switchScalePosition = LL;
    }
    else if (m_randomMessage[0] == 'L' && m_randomMessage[1] == 'R') {
        m_switchScalePosition = LR;
    }
    else if (m_randomMessage[0] == 'R' && m_randomMessage[1] == 'L') {
        m_switchScalePosition = RL;
    }
    else if (m_randomMessage[0] == 'R' && m_randomMessage[1] == 'R') {
        m_switchScalePosition = RR;
    }

    switch (m_disabled->GetStartPosition()) {
        case 1: //left
            switch (m_switchScalePosition) {
                case LL:
                    break;
                case LR:
                    break;
                case RL:
                    break;
                case RR:
                    break;
                default:
                    break;
            }
            break;
        case 2: //center
            switch (m_switchScalePosition) {
                case LL:
                    break;
                case LR:
                    break;
                case RL:
                    break;
                case RR:
                    break;
                default:
                    break;
            }
            break;
        case 3: //right
            switch (m_switchScalePosition) {
                case LL:
                    break;
                case LR:
                    break;
                case RL:
                    break;
                case RR:
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    printf("Auto Routine %d\n", m_disabled->GetRoutine());
    switch (m_disabled->GetRoutine()) {
        case Disabled::SelectedAutoRoutine::none:
            m_noAuto->Reset();
            break;
        case Disabled::SelectedAutoRoutine::forward:
            m_forwardAuto->Reset();
            break;
        default:
            break;
    }
}

void Autonomous::AutonomousPeriodic() {
    switch (m_disabled->GetRoutine()) {
        case Disabled::SelectedAutoRoutine::none:
            m_noAuto->Execute();
            break;
        case Disabled::SelectedAutoRoutine::forward:
            m_forwardAuto->Execute();
            break;
        default:
            break;
    }
}

void Autonomous::AutonomousStop() {
}
};
