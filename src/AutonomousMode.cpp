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
        , m_scoringLocations("")
        , m_switchScalePosition(SwitchScalePosition::LL)
        , m_routine(SelectedAutoRoutine::noAuto) {
}

Autonomous::~Autonomous() {
}

void Autonomous::AutonomousInit() {
    // Remember to zero all sensors here
    std::cout << "Autonomous Start" << std::endl;

    m_scoringLocations = DriverStation::GetInstance().GetGameSpecificMessage();
    DBStringPrintf(DB_LINE1, "%s", m_scoringLocations.c_str());

    switch (m_disabled->GetStartPosition()) {
        case 1:  // left
            switch (GetSwitchScalePosition(m_scoringLocations)) {
                case LL:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::lowGoal;
                    break;
                case LR:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::lowGoal;
                    break;
                case RL:
                    m_scaleAuto->Reset();
                    m_routine = SelectedAutoRoutine::highGoal;
                    break;
                case RR:
                    m_scaleAuto->Reset();
                    m_routine = SelectedAutoRoutine::highGoal;
                    break;
                default:
                    break;
            }
            break;
        case 2:  // center
            switch (GetSwitchScalePosition(m_scoringLocations)) {
                case LL:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::lowGoal;
                    break;
                case LR:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::lowGoal;
                    break;
                case RL:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::lowGoal;
                    break;
                case RR:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::lowGoal;
                    break;
                default:
                    break;
            }
            break;
        case 3:  // right
            switch (GetSwitchScalePosition(m_scoringLocations)) {
                case LL:
                    m_scaleAuto->Reset();
                    m_routine = SelectedAutoRoutine::highGoal;
                    break;
                case LR:
                    m_scaleAuto->Reset();
                    m_routine = SelectedAutoRoutine::highGoal;
                    break;
                case RL:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::highGoal;
                    break;
                case RR:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::highGoal;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    printf("Auto Routine %d\n", m_routine);
}

void Autonomous::AutonomousPeriodic() {
    switch (m_routine) {
        case SelectedAutoRoutine::noAuto:
            m_noAuto->Execute();
            break;
        case SelectedAutoRoutine::forward:
            m_forwardAuto->Execute();
            break;
        case SelectedAutoRoutine::lowGoal:
            m_switchAuto->Execute();
            break;
        case SelectedAutoRoutine::highGoal:
            m_scaleAuto->Execute();
            break;
        default:
            break;
    }
}

void Autonomous::AutonomousStop() {
}

Autonomous::SwitchScalePosition Autonomous::GetSwitchScalePosition(std::string message) {
    if (message[0] == 'L' && message[1] == 'L') {
        m_switchScalePosition = LL;
    }
    else if (message[0] == 'L' && message[1] == 'R') {
        m_switchScalePosition = LR;
    }
    else if (message[0] == 'R' && message[1] == 'L') {
        m_switchScalePosition = RL;
    }
    else if (message[0] == 'R' && message[1] == 'R') {
        m_switchScalePosition = RR;
    }
    return m_switchScalePosition;
}

const char *Autonomous::GetRoutineName() {
    switch (m_routine) {
        case SelectedAutoRoutine::noAuto:
            return "NoAuto";
            break;
        case SelectedAutoRoutine::forward:
            return "ForwardAuto";
            break;
        case SelectedAutoRoutine::lowGoal:
            return "SwitchAuto";
            break;
        case SelectedAutoRoutine::highGoal:
            return "ScaleAuto";
            break;
        default:
            break;
    }
    return "Error initializing auto!";
}
};
