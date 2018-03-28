#include "src/AutonomousMode.h"
#include "src/DisabledMode.h"
#include "src/Robot.h"

using namespace frc;

namespace frc973 {
Autonomous::Autonomous(Disabled *disabled, Drive *drive,
                       IntakeAssembly *intakeAssembly, ADXRS450_Gyro *gyro,
                       GreyLight *greylight)
        : m_noAuto(new NoAuto())
        , m_forwardAuto(new ForwardAuto(drive))
        , m_centerSwitchAuto(new CenterSwitchAuto(drive, intakeAssembly))
        , m_scaleAuto(new ScaleAuto(drive, intakeAssembly))
        , m_scaleOpposite(new ScaleOpposite(drive, intakeAssembly))
        , m_sideSwitch(new SideSwitch(drive, intakeAssembly))
        , m_switchOpposite(new SwitchOpposite(drive, intakeAssembly))
        , m_twoCubeAuto(new TwoCubeAuto(drive, intakeAssembly))
        , m_disabled(disabled)
        , m_greylight(greylight)
        , m_autoSignal(new LightPattern::AutoIndicator())
        , m_scoringLocations("")
        , m_switchScalePosition(SwitchScalePosition::NOT_YET_RECEIVED)
        , m_routine(m_noAuto)
        , m_direction(AutoRoutineBase::AutoDirection::Left)
        , m_drive(drive)
        , m_intakeAssembly(intakeAssembly)
        , m_gyro(gyro) {
}

Autonomous::~Autonomous() {
}

void Autonomous::AutonomousInit() {
    // Remember to zero all sensors here
    m_intakeAssembly->GoToIntakePosition(IntakeAssembly::STOW_PRESET);
    m_gyro->Reset();
    std::cout << "Autonomous Start" << std::endl;

    DBStringPrintf(DB_LINE1, "%s", m_scoringLocations.c_str());
    printf("%s\n", m_scoringLocations.c_str());

    if (GetSwitchScalePosition(m_scoringLocations) ==
        SwitchScalePosition::NOT_YET_RECEIVED) {
        m_scoringLocations =
            DriverStation::GetInstance().GetGameSpecificMessage();
    }

    m_autoSignal->SetData(m_scoringLocations);
    m_greylight->SetPixelStateProcessor(m_autoSignal);

    switch (m_disabled->GetStartPosition()) {
        case AutoRoutineBase::RobotStartPosition::Left:
            switch (GetSwitchScalePosition(m_scoringLocations)) {
                case SwitchScalePosition::LL:
                    m_twoCubeAuto->Reset();
                    m_routine = m_twoCubeAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
                    break;
                case SwitchScalePosition::LR:
                    m_scaleOpposite->Reset();
                    m_routine = m_scaleOpposite;
                    m_direction = AutoRoutineBase::AutoDirection::Right;
                    break;
                case SwitchScalePosition::RL:
                    m_scaleAuto->Reset();
                    m_routine = m_scaleAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
                    break;
                case SwitchScalePosition::RR:
                    m_scaleOpposite->Reset();
                    m_routine = m_scaleOpposite;
                    m_direction = AutoRoutineBase::AutoDirection::Right;
                    break;
                case SwitchScalePosition::NOT_YET_RECEIVED:
                    m_routine = m_forwardAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
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
                case SwitchScalePosition::NOT_YET_RECEIVED:
                    m_routine = m_forwardAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
                    break;
                default:
                    break;
            }
            break;
        case AutoRoutineBase::RobotStartPosition::Right:
            switch (GetSwitchScalePosition(m_scoringLocations)) {
                case SwitchScalePosition::LL:
                    m_switchOpposite->Reset();
                    m_routine = m_switchOpposite;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
                    break;
                case SwitchScalePosition::LR:
                    m_scaleAuto->Reset();
                    m_routine = m_scaleAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Right;
                    break;
                case SwitchScalePosition::RL:
                    m_sideSwitch->Reset();
                    m_routine = m_sideSwitch;
                    m_direction = AutoRoutineBase::AutoDirection::Right;
                    break;
                case SwitchScalePosition::RR:
                    m_scaleAuto->Reset();
                    m_routine = m_scaleAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Right;
                    break;
                case SwitchScalePosition::NOT_YET_RECEIVED:
                    m_routine = m_forwardAuto;
                    m_direction = AutoRoutineBase::AutoDirection::Left;
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
    else {
        m_switchScalePosition = SwitchScalePosition::NOT_YET_RECEIVED;
    }
    return m_switchScalePosition;
}
};
