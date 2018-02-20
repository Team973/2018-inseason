#pragma once

#include "lib/trajectories/structs.h"
#include "stdio.h"
#include <cmath>

namespace trajectories {
double GetLeftDriveVelocity(TrajectoryDescription *trajectory, double time);
double GetRightDriveVelocity(TrajectoryDescription *trajectory, double time);

double GetLeftDist(TrajectoryDescription *trajectory, double time);
double GetRightDist(TrajectoryDescription *trajectory, double time);

double GetHeadingDegrees(TrajectoryDescription *trajectory, double time);
int GetLength(TrajectoryDescription *trajectory);
}