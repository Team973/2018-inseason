#include "src/controllers/SplineDriveController.h"
#include "src/info/RobotInfo.h"
#include "lib/util/Util.h"
#include "lib/util/WrapDash.h"

namespace frc973 {

using namespace Constants;
using namespace trajectories;

SplineDriveController::SplineDriveController(DriveStateProvider *state,
                                             LogSpreadsheet *logger)
        : m_state(state)
        , m_trajectory(nullptr)
        , m_leftDist(0.0)
        , m_rightDist(0.0)
        , m_heading(0.0)
        , m_leftVel(0.0)
        , m_rightVel(0.0)
        , m_left_dist_offset(0.0)
        , m_right_dist_offset(0.0)
        , m_angle_offset(0.0)
        , m_time_offset(0.0)
        , m_done(false)
        , m_l_pos_pid(0.0, 0.0, 0.0)
        , m_l_vel_pid(0.0, 0.0, 0.0)
        , m_r_pos_pid(0.0, 0.0, 0.0)
        , m_r_vel_pid(0.0, 0.0, 0.0)
        , m_a_pos_pid(0.0, 0.0, 0.0)
        , m_l_pos_setpt_log(new LogCell("s_linear pos incr goal"))
        , m_l_pos_real_log(new LogCell("s_linear pos incr actual"))
        , m_l_vel_setpt_log(new LogCell("s_linear vel incr goal"))
        , m_l_vel_real_log(new LogCell("s_linear vel incr actual"))
        , m_a_pos_setpt_log(new LogCell("s_angular pos incr goal"))
        , m_a_pos_real_log(new LogCell("s_angular pos incr actual"))
        , m_dist_endgoal_log(new LogCell("s_linear pos end goal"))
        , m_angle_endgoal_log(new LogCell("s_angle pos end goal"))
        , m_left_output(new LogCell("s_left output"))
        , m_right_output(new LogCell("s_right output")) {
    m_l_pos_pid.SetBounds(-100, 100);
    m_l_vel_pid.SetBounds(-100, 100);
    m_a_pos_pid.SetBounds(-100, 100);

    if (logger) {
        logger->RegisterCell(m_l_pos_setpt_log);
        logger->RegisterCell(m_l_pos_real_log);
        logger->RegisterCell(m_l_vel_setpt_log);
        logger->RegisterCell(m_l_vel_real_log);
        logger->RegisterCell(m_a_pos_setpt_log);
        logger->RegisterCell(m_a_pos_real_log);
        logger->RegisterCell(m_dist_endgoal_log);
        logger->RegisterCell(m_angle_endgoal_log);
        logger->RegisterCell(m_left_output);
        logger->RegisterCell(m_right_output);
    }
}

SplineDriveController::~SplineDriveController() {
    ;
}

void SplineDriveController::SetTarget(TrajectoryDescription *trajectory) {
    m_time_offset = GetSecTime();

    m_left_dist_offset = m_state->GetLeftDist();
    m_right_dist_offset = m_state->GetRightDist();

    m_angle_offset = m_state->GetAngle();

    m_trajectory = trajectory;
}

void SplineDriveController::CalcDriveOutput(DriveStateProvider *state,
                                            DriveControlSignalReceiver *out) {
    double time = GetSecTime() - m_time_offset;

    /* printf(
         "Spline drive d %lf a %lf vel %lf acc %lf start %lf end "
         "%lf\n",
         m_dist, m_angle, m_max_vel, m_max_acc, m_start_vel, m_end_vel);
     DBStringPrintf(DB_LINE3, "lo%0.3lf ro%0.3lf", m_left_output,
                    m_right_output);*/

    m_leftDist = trajectories::GetLeftDist(m_trajectory, time);
    m_rightDist = trajectories::GetRightDist(m_trajectory, time);
    m_leftVel = trajectories::GetLeftDriveVelocity(m_trajectory, time);
    m_rightVel = trajectories::GetRightDriveVelocity(m_trajectory, time);
    m_heading = trajectories::GetHeading(m_trajectory, time);

    m_l_pos_pid.SetTarget(m_leftDist);
    m_r_pos_pid.SetTarget(m_rightDist);
    m_l_vel_pid.SetTarget(m_leftVel);
    m_r_vel_pid.SetTarget(m_rightVel);
    m_a_pos_pid.SetTarget(m_heading);

    /* vel feed forward for linear term */
    double right_l_vel_ff =
        trajectories::GetRightDriveVelocity(m_trajectory, time);
    double left_l_vel_ff =
        trajectories::GetLeftDriveVelocity(m_trajectory, time);

    /* correction terms for error in {linear,angular} {position,velocioty */
    double linear_dist_term = m_l_pos_pid.CalcOutput(LeftDistFromStart());
    double linear_vel_term = m_l_vel_pid.CalcOutput(state->GetRate());
    double angular_dist_term = m_a_pos_pid.CalcOutput(AngleFromStart());

    /* right side receives positive angle correction */
    double right_output =
        right_l_vel_ff + linear_dist_term + linear_vel_term + angular_dist_term;
    /* left side receives negative angle correction */
    double left_output =
        left_l_vel_ff + linear_dist_term + linear_vel_term - angular_dist_term;

    out->SetDriveOutputIPS(left_output, right_output);

    if (time < trajectories::GetLength(m_trajectory) * 0.01) {
        m_done = false;
    }
    else {
        m_done = true;
    }

    /*m_l_pos_setpt_log->LogDouble(goal.linear_dist);
    m_l_pos_real_log->LogDouble(DistFromStart());
    m_l_vel_setpt_log->LogDouble(goal.linear_vel);
    m_l_vel_real_log->LogDouble(state->GetRate());
    m_a_pos_setpt_log->LogDouble(goal.angular_dist);
    m_a_pos_real_log->LogDouble(AngleFromStart());
    m_dist_endgoal_log->LogDouble(m_dist);
    m_angle_endgoal_log->LogDouble(m_angle);
    m_left_output->LogDouble(left_output);
    m_right_output->LogDouble(right_output);*/
}

void SplineDriveController::Start() {
}

void SplineDriveController::Stop() {
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
