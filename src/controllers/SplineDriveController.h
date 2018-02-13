/**
 * SplineDriveController.h
 * Created On: Feb 12, 2018
 * Author: Kyle
 *
 **/

#pragma once

#include "lib/bases/DriveBase.h"
#include "lib/helpers/PID.h"
#include "lib/logging/LogSpreadsheet.h"
#include "lib/trajectories/SplineProfile.h"
#include "ctre/Phoenix.h"
#include "lib/trajectories/structs.h"
#include <stdio.h>

using namespace frc;
using namespace trajectories;

namespace frc973 {

class SplineDriveController : public DriveController {
public:
    SplineDriveController(DriveStateProvider *state, LogSpreadsheet *logger);
    virtual ~SplineDriveController();

    void SetTarget(TrajectoryDescription *trajectory);

    void CalcDriveOutput(DriveStateProvider *state,
                         DriveControlSignalReceiver *out) override;

    bool OnTarget() override {
        return m_done;
    }

    void Start() override;

    void Stop() override;

    double LeftDistFromStart() const;
    double RightDistFromStart() const;
    double AngleFromStart() const;

private:
    DriveStateProvider *m_state;
    TrajectoryDescription *m_trajectory;
    double m_leftDist, m_rightDist, m_heading;
    double m_leftVel, m_rightVel;
    double m_left_dist_offset, m_right_dist_offset, m_angle_offset,
        m_time_offset;
    bool m_done;

    /* pid for linear {pos,vel} */
    PID m_l_pos_pid, m_l_vel_pid;
    PID m_r_pos_pid, m_r_vel_pid;

    /* pid for angular pos */
    PID m_a_pos_pid;

    LogCell *m_l_pos_setpt_log;
    LogCell *m_l_pos_real_log;
    LogCell *m_l_vel_setpt_log;
    LogCell *m_l_vel_real_log;
    LogCell *m_r_pos_setpt_log;
    LogCell *m_r_pos_real_log;
    LogCell *m_r_vel_setpt_log;
    LogCell *m_r_vel_real_log;
    LogCell *m_a_pos_setpt_log;
    LogCell *m_a_pos_real_log;
    LogCell *m_left_dist_endgoal_log;
    LogCell *m_right_dist_endgoal_log;
    LogCell *m_angle_endgoal_log;
    LogCell *m_left_output;
    LogCell *m_right_output;
};
}
