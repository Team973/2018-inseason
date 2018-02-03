#pragma once

namespace frc973 {
  struct TrajectoryDescription {
  const double timestep;
  const double max_vel;
  const double max_accel;
  const double max_jerk;
  const double wheelbase_width;
  const int length;
  const Segment *left_trajectory;
  const Segment *right_trajectory;

  TrajectoryDescription(double timestep_,
           double max_vel_,
           double max_accel_,
           double max_jerk_,
           double wheelbase_width_,
           int length_,
           Segment *left_trajectory_,
           Segment *right_trajectory_)
        : timestep(timestep_)
        , max_vel(max_vel_)
        , max_accel(max_accel_)
        , max_jerk(max_jerk_)
        , wheelbase_width(wheelbase_width_)
        , length(length_)
        , left_trajectory(left_trajectory_)
        , right_trajectory(right_trajectory_){
   }
};
}
