/**
 * Limelight.h
 *
 * Authors: Kyle, Chris M.
 **/
#pragma once

#include "WPILib.h"
#include "lib/util/WrapDash.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/NetworkTableEntry.h"

using namespace frc;

namespace frc973 {

class Limelight {
public:
    Limelight();
    virtual ~Limelight();

    enum class LightMode
    {
        on,
        off,
        blink
    };

    /**
     * onVision: Uses tuned settings and sends values to NetworkTables
     * onDriver: Higher exposure relative to onVision for  streaming and turns
     *off vision processing
     **/
    enum class CameraMode
    {
        onVision,
        onDriver
    };

    void SetLightMode();
    void SetCameraMode();

    void SetLightOn();
    void SetLightOff();
    void SetLightBlink();

    void SetCameraVision();
    void SetCameraDriver();

    bool isTargetValid();

    double GetXOffset();
    double GetYOffset();
    double GetTargetArea();
    double GetTargetSkew();
    double GetLatency();

private:
    std::shared_ptr<NetworkTable> m_limelight;

    LightMode m_lightMode;
    CameraMode m_cameraMode;

    bool m_targetStatus;

    double m_horizontalOffset;
    double m_verticalOffset;
    double m_targetArea;
    double m_targetSkew;
    double m_latency;
};
}
