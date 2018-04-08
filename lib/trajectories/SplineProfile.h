#pragma once

#include "lib/trajectories/structs.h"
#include "stdio.h"
#include <cmath>

namespace trajectories {
double GetLeftDriveVelocity(TrajectoryDescription *trajectory, double time);
double GetRightDriveVelocity(TrajectoryDescription *trajectory, double time);

double GetLeftDist(TrajectoryDescription *trajectory, double time);
double GetRightDist(TrajectoryDescription *trajectory, double time);

double GetLeftAcceleration(TrajectoryDescription *trajectory, double time);
double GetRightAcceleration(TrajectoryDescription *trajectory, double time);

double GetHeadingDegrees(TrajectoryDescription *trajectory, double time);
int GetLength(TrajectoryDescription *trajectory);
double GetPercentComplete(TrajectoryDescription *trajectory, double time);

double GetAngularRateDegrees(TrajectoryDescription *trajectory, double time);
double GetAngularAcceleration(TrajectoryDescription *trajectory, double time);
}
