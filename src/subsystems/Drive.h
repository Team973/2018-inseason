#include <TalonSRX.h>
#include <VictorSPX.h>
using namespace ctre::phoenix::motorcontrol::can

class Drive {
    private:
        *TalonSRX m_leftTalon, m_rightTalon;
        *VictorSPX m_slaveLeftone, m_slaveLefttwo, m_slaveRightone, m_slaveRighttwo;
    public:
         Drive(*TalonSRX leftTalon, *TalonSRX rightTalon, *VictorSPX slaveLeftone,
               *VictorSPX slaveLefttwo, *VictorSPX slaveRightone, *VictorSPX slaveRighttwo);

