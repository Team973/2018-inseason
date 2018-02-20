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
        , m_switchAuto(new SwitchAuto())
        , m_disabled(disabled) {
}

Autonomous::~Autonomous() {
}

void Autonomous::AutonomousInit() {
    // Remember to zero all sensors here
    std::cout << "Autonomous Start" << std::endl;
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
