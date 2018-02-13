#include "lib/trajectories/SplineProfile.h"
#include "lib/trajectories/structs.h"

namespace trajectories {
double GetLeftDriveVelocity(TrajectoryDescription *trajectory, double time) {
    int index = (int)(time / trajectory->left_trajectory->dt);
    return trajectory->left_trajectory[index].velocity;
}

double GetRightDriveVelocity(TrajectoryDescription *trajectory, double time) {
    int index = (int)(time / trajectory->right_trajectory->dt);
    return trajectory->right_trajectory[index].velocity;
}

double GetLeftDist(TrajectoryDescription *trajectory, double time) {
    int index = (int)(time / trajectory->left_trajectory->dt);
    return trajectory->left_trajectory[index].position;
}

double GetRightDist(TrajectoryDescription *trajectory, double time) {
    int index = (int)(time / trajectory->right_trajectory->dt);
    return trajectory->right_trajectory[index].position;
}

double GetHeading(TrajectoryDescription *trajectory, double time) {
    int index = (int)(time / trajectory->left_trajectory->dt);
    return trajectory->left_trajectory[index].heading;
}

int GetLength(TrajectoryDescription *trajectory) {
    return trajectory->length;
}
}
