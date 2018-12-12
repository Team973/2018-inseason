#include "lib/sensors/Limelight.h"

using namespace frc;

namespace frc973 {
Limelight::Limelight()
        : m_limelight(
              nt::NetworkTableInstance::GetDefault().GetTable("limelight"))
        , m_lightMode(LightMode::on)
        , m_cameraMode(CameraMode::onVision)
        , m_targetStatus(false)
        , m_horizontalOffset(0.0)
        , m_verticalOffset(0.0)
        , m_targetArea(0.0)
        , m_targetSkew(0.0)
        , m_latency(0.0) {
}

Limelight::~Limelight() {
}

void Limelight::SetLightMode() {
    switch (m_lightMode) {
        case LightMode::on:
            m_limelight->PutNumber("ledMode", 0);
            break;
        case LightMode::off:
            m_limelight->PutNumber("ledMode", 1);
            break;
        case LightMode::blink:
            m_limelight->PutNumber("ledMode", 2);
            break;
    }
}

void Limelight::SetCameraMode() {
    switch (m_cameraMode) {
        case CameraMode::onVision:
            m_limelight->PutNumber("camMode", 0);
            break;
        case CameraMode::onDriver:
            m_limelight->PutNumber("camMode", 1);
            break;
    }
}

void Limelight::SetLightOn() {
    m_lightMode = LightMode::on;
    Limelight::SetLightMode();
}

void Limelight::SetLightOff() {
    m_lightMode = LightMode::off;
    Limelight::SetLightMode();
}

void Limelight::SetLightBlink() {
    m_lightMode = LightMode::blink;
    Limelight::SetLightMode();
}

void Limelight::SetCameraVision() {
    m_cameraMode = CameraMode::onVision;
    Limelight::SetCameraMode();
}

void Limelight::SetCameraDriver() {
    m_cameraMode = CameraMode::onDriver;
    Limelight::SetCameraMode();
}

bool Limelight::isTargetValid() {
    return m_limelight->GetNumber("tv", 0.0);
}

double Limelight::GetXOffset() {
    return m_limelight->GetNumber("tx", 0.0);
}

double Limelight::GetYOffset() {
    return m_limelight->GetNumber("ty", 0.0);
}

double Limelight::GetTargetArea() {
    return m_limelight->GetNumber("ta", 0.0);
}

double Limelight::GetTargetSkew() {
    return m_limelight->GetNumber("ts", 0.0);
}

double Limelight::GetLatency() {
    return m_limelight->GetNumber("tl", 0.0);
}
}
