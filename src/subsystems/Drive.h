#include <TalonSRX.h>
#include <VictorSPX.h>
#include <ADXRS450_Gyro.h>
using namespace ctre::phoenix::motorcontrol::can;
using namespace frc;

class Drive {
    private:
        TalonSRX *m_leftTalon, *m_rightTalon;
        VictorSPX *m_slaveLeftone, *m_slaveLefttwo, *m_slaveRightone, *m_slaveRighttwo;
        ADXRS450_Gyro *m_driveGyro;
    public:
         Drive(TalonSRX *leftTalon, TalonSRX *rightTalon, VictorSPX *slaveLeftone,
               VictorSPX *slaveLefttwo, VictorSPX *slaveRightone, VictorSPX *slaveRighttwo, ADXRS450_Gyro *driveGyro);

