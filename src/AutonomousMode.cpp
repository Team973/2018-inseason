#include "src/AutonomousMode.h"
#include "src/auto/NoAuto.h"
#include "src/auto/ForwardAuto.h"
#include "src/DisabledMode.h"
#include "src/Robot.h"

using namespace frc;

namespace frc973 {
Autonomous::Autonomous(Disabled *disabled, Drive *drive, Elevator *elevator,
                       Claw *claw, ADXRS450_Gyro *gyro)
        : m_noAuto(new NoAuto())
        , m_forwardAuto(new ForwardAuto(drive))
        , m_switchAuto(new SwitchAuto(drive, elevator, claw))
        , m_disabled(disabled)
        , m_scoringLocations("")
        , m_switchScalePosition(SwitchScalePosition::LL)
        , m_routine(SelectedAutoRoutine::noAuto)
        , m_drive(drive)
        , m_elevator(elevator)
        , m_claw(claw)
        , m_gyro(gyro) {
}

Autonomous::~Autonomous() {
}

void Autonomous::AutonomousInit() {
    // Remember to zero all sensors here
    m_elevator->SetPosition(Elevator::GROUND);
    m_gyro->Reset();
    m_claw->grab();
    std::cout << "Autonomous Start" << std::endl;

    m_scoringLocations = DriverStation::GetInstance().GetGameSpecificMessage();
    DBStringPrintf(DB_LINE1, "%s", m_scoringLocations.c_str());
    printf("%s\n", m_scoringLocations.c_str());

    switch (m_disabled->GetStartPosition()) {
        case Disabled::RobotStartPosition::Left:
            switch (GetSwitchScalePosition(m_scoringLocations)) {
                case SwitchScalePosition::LL:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::lowGoal;
                    break;
                case SwitchScalePosition::LR:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::lowGoal;
                    break;
                case SwitchScalePosition::RL:
                    m_scaleAuto->Reset();
                    m_routine = SelectedAutoRoutine::highGoal;
                    break;
                case SwitchScalePosition::RR:
                    m_scaleAuto->Reset();
                    m_routine = SelectedAutoRoutine::highGoal;
                    break;
                default:
                    break;
            }
            break;
        case Disabled::RobotStartPosition::Center:
            printf("Center Auto\n");
            switch (GetSwitchScalePosition(m_scoringLocations)) {
                case SwitchScalePosition::LL:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::lowGoal;
                    break;
                case SwitchScalePosition::LR:
                    printf("Forward Auto\n");
                    m_forwardAuto->Reset();
                    m_routine = SelectedAutoRoutine::forward;
                    break;
                case SwitchScalePosition::RL:
                    m_forwardAuto->Reset();
                    m_routine = SelectedAutoRoutine::forward;
                    break;
                case SwitchScalePosition::RR:
                    m_forwardAuto->Reset();
                    m_routine = SelectedAutoRoutine::forward;
                    break;
                default:
                    break;
            }
            break;
        case Disabled::RobotStartPosition::Right:
            switch (GetSwitchScalePosition(m_scoringLocations)) {
                case SwitchScalePosition::LL:
                    m_scaleAuto->Reset();
                    m_routine = SelectedAutoRoutine::highGoal;
                    break;
                case SwitchScalePosition::LR:
                    m_scaleAuto->Reset();
                    m_routine = SelectedAutoRoutine::highGoal;
                    break;
                case SwitchScalePosition::RL:
                    m_switchAuto->Reset();
                    m_routine = SelectedAutoRoutine::highGoal;
                    break;
                case SwitchScalePosition::RR:
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

Autonomous::SwitchScalePosition Autonomous::GetSwitchScalePosition(
    std::string message) {
    if (message[0] == 'L' && message[1] == 'L') {
        m_switchScalePosition = SwitchScalePosition::LL;
    }
    else if (message[0] == 'L' && message[1] == 'R') {
        m_switchScalePosition = SwitchScalePosition::LR;
    }
    else if (message[0] == 'R' && message[1] == 'L') {
        m_switchScalePosition = SwitchScalePosition::RL;
    }
    else if (message[0] == 'R' && message[1] == 'R') {
        m_switchScalePosition = SwitchScalePosition::RR;
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
