#pragma once

#include "lib/bases/DriveBase.h"
#include "lib/helpers/PID.h"
#include "lib/logging/LogSpreadsheet.h"
#include <stdio.h>

using namespace frc;
using namespace ctre;

namespace frc973 {

class SplineDriveController: public DriveController {
public:
    SplineDriveController(DriveStateProvider *state, LogSpreadsheet *logger);
    virtual ~SplineDriveController();

    void SetTarget(DriveBase::RelativeTo relativeTo,
                   double dist, double angle);

    SplineDriveController *SetHalt(bool start_halt, bool end_halt);
    SplineDriveController *SetConstraints(double max_vel, double max_acc);

    void CalcDriveOutput(DriveStateProvider *state,
            DriveControlSignalReceiver *out) override;

    bool OnTarget() override { return m_done; }

    void Start() override {
        printf("Turning on Spline Mode\n");
    }

    void Stop() override {
        printf("Turning off Spline Mode\n");
    }

    double DistFromStart() const;
    double AngleFromStart() const;
private:
    DriveStateProvider *m_state;
    double m_dist, m_angle;
    double m_dist_offset, m_angle_offset, m_time_offset;
    double m_max_vel, m_max_acc;
    bool m_start_halt, m_end_halt;

    /* pid for linear {pos,vel} */
    PID m_l_pos_pid, m_l_vel_pid;

    /* pid for angular {pos,vel} */
    PID m_a_pos_pid, m_a_vel_pid;

    bool m_done;

    static constexpr double MAX_VELOCITY = 130;     //in/sec
    static constexpr double MAX_ACCELERATION = 10.0; //in/sec^2

    LogCell *m_l_pos_setpt_log;
    LogCell *m_l_pos_real_log;
    LogCell *m_l_vel_setpt_log;
    LogCell *m_l_vel_real_log;
    LogCell *m_a_pos_setpt_log;
    LogCell *m_a_pos_real_log;
    LogCell *m_a_vel_setpt_log;
    LogCell *m_max_vel_log;
    LogCell *m_max_acc_log;
    LogCell *m_dist_endgoal_log;
    LogCell *m_angle_endgoal_log;
};

}
