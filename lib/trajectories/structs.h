#pragma once

struct {
    const double dt;
    const double x;
    const double y;
    const double position;
    const double velocity;
    const double acceleration;
    const double jerk;
    const double heading;
} Segment;

struct TrajectoryDescription {
    const double timestep;
    const double max_vel;
    const double max_accel;
    const double max_jerk;
    const double wheelbase_width;
    const int length;
    const Segment *left_trajectory;
    const Segment *right_trajectory;
};
