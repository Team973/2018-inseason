#pragma once

namespace trajectories {

struct Segment {
    double dt;
    double x;
    double y;
    double position;
    double velocity;
    double acceleration;
    double jerk;
    double heading;
    double angular_rate;
    double angular_accel;
};

struct TrajectoryDescription {
    double timestep;
    double max_vel;
    double max_accel;
    double max_jerk;
    double wheelbase_width;
    int length;
    Segment *left_trajectory;
    Segment *right_trajectory;
};
}
