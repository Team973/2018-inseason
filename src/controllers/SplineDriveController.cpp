#include "src/controllers/SplineDriveController.h"
#include "src/info/RobotInfo.h"
#include "lib/util/Util.h"
#include "lib/util/WrapDash.h"
#include <cmath>

namespace frc973 {

using namespace Constants;
using namespace trajectories;

static constexpr double POSITION_KP = 1.5;
static constexpr double POSITION_KI = 0.0;
static constexpr double POSITION_KD = 0.0;

static constexpr double VELOCITY_KP = 1.0;
static constexpr double VELOCITY_KI = 0.0;
static constexpr double VELOCITY_KD = 0.0;

static constexpr double ANGULAR_POSITION_KP = 3.6;
static constexpr double ANGULAR_POSITION_KI = 0.0;
static constexpr double ANGULAR_POSITION_KD = 0.0;

static constexpr double ACCEL_FF = 0.4;

SplineDriveController::SplineDriveController(DriveStateProvider *state,
                                             LogSpreadsheet *logger)
        : DriveController()
        , m_state(state)
        , m_trajectory(nullptr)
        , m_left_dist_offset(0.0)
        , m_right_dist_offset(0.0)
        , m_angle_offset(0.0)
        , m_time_offset(0.0)
        , m_done(false)
        , m_l_pos_pid(POSITION_KP, POSITION_KI, VELOCITY_KD)
        , m_l_vel_pid(VELOCITY_KP, VELOCITY_KI, VELOCITY_KD)
        , m_r_pos_pid(POSITION_KP, POSITION_KI, POSITION_KD)
        , m_r_vel_pid(VELOCITY_KP, VELOCITY_KI, VELOCITY_KD)
        , m_a_pos_pid(ANGULAR_POSITION_KP, ANGULAR_POSITION_KI,
                      ANGULAR_POSITION_KD)
        , m_l_pos_setpt_log(new LogCell("s_left pos incr goal"))
        , m_l_pos_real_log(new LogCell("s_left pos incr actual"))
        , m_l_vel_setpt_log(new LogCell("s_left vel incr goal"))
        , m_l_vel_real_log(new LogCell("s_left vel incr actual"))
        , m_r_pos_setpt_log(new LogCell("s_right pos incr goal"))
        , m_r_pos_real_log(new LogCell("s_right pos incr actual"))
        , m_r_vel_setpt_log(new LogCell("s_right vel incr goal"))
        , m_r_vel_real_log(new LogCell("s_right vel incr actual"))
        , m_a_pos_setpt_log(new LogCell("s_angular pos incr goal"))
        , m_a_pos_real_log(new LogCell("s_angular pos incr actual"))
        , m_angle_endgoal_log(new LogCell("s_angle pos end goal"))
        , m_left_output(new LogCell("s_left output"))
        , m_right_output(new LogCell("s_right output")) {
    m_l_pos_pid.SetBounds(-100, 100);
    m_l_vel_pid.SetBounds(-100, 100);
    m_r_pos_pid.SetBounds(-100, 100);
    m_r_vel_pid.SetBounds(-100, 100);
    m_a_pos_pid.SetBounds(-100, 100);

    if (logger) {
        logger->RegisterCell(m_l_pos_setpt_log);
        logger->RegisterCell(m_l_pos_real_log);
        logger->RegisterCell(m_l_vel_setpt_log);
        logger->RegisterCell(m_l_vel_real_log);
        logger->RegisterCell(m_r_pos_setpt_log);
        logger->RegisterCell(m_r_pos_real_log);
        logger->RegisterCell(m_r_vel_setpt_log);
        logger->RegisterCell(m_r_vel_real_log);
        logger->RegisterCell(m_a_pos_setpt_log);
        logger->RegisterCell(m_a_pos_real_log);
        logger->RegisterCell(m_angle_endgoal_log);
        logger->RegisterCell(m_left_output);
        logger->RegisterCell(m_right_output);
    }
}

SplineDriveController::~SplineDriveController() {
    ;
}

void SplineDriveController::SetTarget(TrajectoryDescription *trajectory,
                                      DriveBase::RelativeTo relativity) {
    m_time_offset = GetSecTime();

    m_left_dist_offset = m_state->GetLeftDist();
    m_right_dist_offset = m_state->GetRightDist();

    m_trajectory = trajectory;

    switch (relativity) {
        case DriveBase::RelativeTo::Now:
            m_angle_offset = m_state->GetAngle();
            break;
        case DriveBase::RelativeTo::SetPoint:
            break;
        case DriveBase::RelativeTo::Absolute:
            break;
    }
}

void SplineDriveController::CalcDriveOutput(DriveStateProvider *state,
                                            DriveControlSignalReceiver *out) {
    double time = GetSecTime() - m_time_offset;

    double leftDist = trajectories::GetLeftDist(m_trajectory, time);
    double rightDist = trajectories::GetRightDist(m_trajectory, time);
    double leftVel = trajectories::GetLeftDriveVelocity(m_trajectory, time);
    double rightVel = trajectories::GetRightDriveVelocity(m_trajectory, time);
    double heading = trajectories::GetHeadingDegrees(m_trajectory, time);

    m_l_pos_pid.SetTarget(leftDist);
    m_r_pos_pid.SetTarget(rightDist);
    m_l_vel_pid.SetTarget(leftVel);
    m_r_vel_pid.SetTarget(rightVel);
    // m_a_pos_pid.SetTarget(heading);
    double angle_error =
        std::fmod(heading - AngleFromStart() + 180.0, 360.0) - 180.0;

    /* vel feed forward for linear term */
    double right_l_vel_ff =
        trajectories::GetRightDriveVelocity(m_trajectory, time);
    double left_l_vel_ff =
        trajectories::GetLeftDriveVelocity(m_trajectory, time);
    double leftAccel_ff =
        ACCEL_FF * trajectories::GetLeftAcceleration(m_trajectory, time);
    double rightAccel_ff =
        ACCEL_FF * trajectories::GetRightAcceleration(m_trajectory, time);

    /* correction terms for error in {linear,angular} {position,velocioty */
    double left_linear_dist_term = m_l_pos_pid.CalcOutput(LeftDistFromStart());
    double left_linear_vel_term = m_l_vel_pid.CalcOutput(state->GetLeftRate());
    double right_linear_dist_term =
        m_r_pos_pid.CalcOutput(RightDistFromStart());
    double right_linear_vel_term =
        m_r_vel_pid.CalcOutput(state->GetRightRate());
    double angular_dist_term =
        ANGULAR_POSITION_KP *
        angle_error;  // m_a_pos_pid.CalcOutput(AngleFromStart());

    /* right side receives positive angle correction */
    double right_output = right_l_vel_ff + right_linear_dist_term +
                          right_linear_vel_term + angular_dist_term +
                          rightAccel_ff;
    /* left side receives negative angle correction */
    double left_output = left_l_vel_ff + left_linear_dist_term +
                         left_linear_vel_term - angular_dist_term +
                         leftAccel_ff;

    out->SetDriveOutputIPS(left_output, right_output);

    if (time < trajectories::GetLength(m_trajectory) *
                   m_trajectory->left_trajectory->dt) {
        m_done = false;
    }
    else {
        printf("Done\n");
        m_done = true;
    }

    SmartDashboard::PutNumber("drive/outputs/anglesetpoint", heading - 360.0);
    SmartDashboard::PutNumber("drive/outputs/angleactual", AngleFromStart());
    SmartDashboard::PutNumber("drive/outputs/leftpossetpoint", leftDist);
    SmartDashboard::PutNumber("drive/outputs/rightpossetpoint", rightDist);
    SmartDashboard::PutNumber("drive/outputs/leftvelff", left_l_vel_ff);
    SmartDashboard::PutNumber("drive/outputs/rightvelff", right_l_vel_ff);

    DBStringPrintf(DB_LINE1, "lo%0.3lf ro%0.3lf", m_left_output,
                   m_right_output);
    DBStringPrintf(DB_LINE2, "lpset%2.2lf lp%2.2lf", leftDist,
                   LeftDistFromStart());
    DBStringPrintf(DB_LINE3, "lvset%2.2lf lv%2.2lf", leftVel,
                   state->GetLeftRate());
    DBStringPrintf(DB_LINE4, "rpset%2.2lf rp%2.2lf", rightDist,
                   RightDistFromStart());
    DBStringPrintf(DB_LINE5, "rvset%2.2lf rv%2.2lf", rightVel,
                   state->GetRightRate());
    DBStringPrintf(DB_LINE6, "apset%2.2lf ap%2.2lf", heading, AngleFromStart());

    m_l_pos_setpt_log->LogDouble(leftDist);
    m_l_pos_real_log->LogDouble(LeftDistFromStart());
    m_l_vel_setpt_log->LogDouble(leftVel);
    m_l_vel_real_log->LogDouble(state->GetLeftRate());
    m_r_pos_setpt_log->LogDouble(rightDist);
    m_r_pos_real_log->LogDouble(RightDistFromStart());
    m_r_vel_setpt_log->LogDouble(rightVel);
    m_r_vel_real_log->LogDouble(state->GetRightRate());
    m_a_pos_setpt_log->LogDouble(heading);
    m_a_pos_real_log->LogDouble(AngleFromStart());
    m_angle_endgoal_log->LogDouble(heading);
    m_left_output->LogDouble(left_output);
    m_right_output->LogDouble(right_output);
}

void SplineDriveController::Start() {
}

void SplineDriveController::Stop() {
}

double SplineDriveController::GetSplinePercentComplete() const {
    return trajectories::GetPercentComplete(m_trajectory,
                                            GetSecTime() - m_time_offset);
}

double SplineDriveController::LeftDistFromStart() const {
    return m_state->GetLeftDist() - m_left_dist_offset;
}

double SplineDriveController::RightDistFromStart() const {
    return m_state->GetRightDist() - m_right_dist_offset;
}

double SplineDriveController::AngleFromStart() const {
    return m_state->GetAngle() - m_angle_offset;
}
}
