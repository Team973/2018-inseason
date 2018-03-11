#include "src/AutonomousMode.h"
#include "src/DisabledMode.h"
#include "src/Robot.h"

using namespace frc;

namespace frc973 {
Autonomous::Autonomous(Disabled *disabled, Drive *drive, Elevator *elevator,
                       Intake *intake, Claw *claw, ADXRS450_Gyro *gyro)
        : m_noAuto(new NoAuto())
        , m_centerSwitchAuto(
              new CenterSwitchAuto(drive, elevator, intake, claw))
        , m_scaleAuto(new ScaleAuto(drive, elevator, intake, claw))
        , m_scaleOpposite(new ScaleOpposite(drive, elevator, intake, claw))
        , m_sideSwitch(new SideSwitch(drive, elevator, intake, claw))
        , m_switchOpposite(new SwitchOpposite(drive, elevator, intake, claw))
        , m_twoCubeAuto(new TwoCubeAuto(drive, elevator, intake, claw))
        , m_disabled(disabled)
        , m_scoringLocations("")
        , m_switchScalePosition(SwitchScalePosition::NOT_YET_RECEIVED)
        , m_routine(m_noAuto)
        , m_direction(AutoRoutineBase::AutoDirection::Left)
        , m_drive(drive)
        , m_elevator(elevator)
        , m_intake(intake)
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

    DBStringPrintf(DB_LINE1, "%s", m_scoringLocations.c_str());
    printf("%s\n", m_scoringLocations.c_str());

    if (GetSwitchScalePosition(m_scoringLocations) ==
        SwitchScalePosition::NOT_YET_RECEIVED) {
        m_scoringLocations =
            DriverStation::GetInstance().GetGameSpecificMessage();
    }

    switch (m_disabled->GetStartPosition()) {
        case AutoRoutineBase::RobotStartPosition::Left:
            switch (GetSwitchScalePosition(m_scoringLocations)) {
                case SwitchScalePosition::LL:
                    m_twoCubeAuto->Reset();
                    m_routine = m_twoCubeAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
                    break;
                case SwitchScalePosition::LR:
                    m_sideSwitch->Reset();
                    m_routine = m_sideSwitch;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
                    break;
                case SwitchScalePosition::RL:
                    m_switchOpposite->Reset();
                    m_routine = m_scaleAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
                    break;
                case SwitchScalePosition::RR:
                    m_switchOpposite->Reset();
                    m_routine = m_scaleOpposite;
                    m_direction = AutoRoutineBase::AutoDirection::Right;
                    break;
                default:
                    break;
            }
            break;
        case AutoRoutineBase::RobotStartPosition::Center:
            printf("Center Auto\n");
            switch (GetSwitchScalePosition(m_scoringLocations)) {
                case SwitchScalePosition::LL:
                    m_scaleAuto->Reset();
                    m_routine = m_centerSwitchAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
                    break;
                case SwitchScalePosition::LR:
                    m_centerSwitchAuto->Reset();
                    m_routine = m_centerSwitchAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
                    break;
                case SwitchScalePosition::RL:
                    m_centerSwitchAuto->Reset();
                    m_routine = m_centerSwitchAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Right;
                    break;
                case SwitchScalePosition::RR:
                    m_centerSwitchAuto->Reset();
                    m_routine = m_centerSwitchAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Right;
                    break;
                default:
                    break;
            }
            break;
        case AutoRoutineBase::RobotStartPosition::Right:
            switch (GetSwitchScalePosition(m_scoringLocations)) {
                case SwitchScalePosition::LL:
                    m_switchOpposite->Reset();
                    m_routine = m_scaleOpposite;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
                    break;
                case SwitchScalePosition::LR:
                    m_switchOpposite->Reset();
                    m_routine = m_switchOpposite;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
                    break;
                case SwitchScalePosition::RL:
                    m_sideSwitch->Reset();
                    m_routine = m_sideSwitch;
                    m_direction = AutoRoutineBase::AutoDirection::Right;
                    break;
                case SwitchScalePosition::RR:
                    m_scaleAuto->Reset();
                    m_routine = m_twoCubeAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Right;
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
    m_routine->Execute(m_direction);
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
    else if (message == "") {
        m_switchScalePosition = SwitchScalePosition::NOT_YET_RECEIVED;
    }
    return m_switchScalePosition;
}
};
