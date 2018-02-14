#include "lib/trajectories/SplineProfile.h"
#include "lib/trajectories/structs.h"

namespace trajectories {
double GetLeftDriveVelocity(TrajectoryDescription *trajectory, double time) {
    int index = (int)(time / trajectory->left_trajectory->dt);
    if (index > GetLength(trajectory)) {
        return trajectory->left_trajectory[GetLength(trajectory)].velocity;
    }
    return trajectory->left_trajectory[index].velocity;
}

double GetRightDriveVelocity(TrajectoryDescription *trajectory, double time) {
    int index = (int)(time / trajectory->right_trajectory->dt);
    if (index > GetLength(trajectory)) {
        return trajectory->right_trajectory[GetLength(trajectory)].velocity;
    }
    return trajectory->right_trajectory[index].velocity;
}

double GetLeftDist(TrajectoryDescription *trajectory, double time) {
    int index = (int)(time / trajectory->left_trajectory->dt);
    if (index > GetLength(trajectory)) {
        return trajectory->left_trajectory[GetLength(trajectory)].position;
    }
    return trajectory->left_trajectory[index].position;
}

double GetRightDist(TrajectoryDescription *trajectory, double time) {
    int index = (int)(time / trajectory->right_trajectory->dt);
    if (index > GetLength(trajectory)) {
        return trajectory->right_trajectory[GetLength(trajectory)].position;
    }
    return trajectory->right_trajectory[index].position;
}

double GetHeading(TrajectoryDescription *trajectory, double time) {
    int index = (int)(time / trajectory->left_trajectory->dt);
    if (index > GetLength(trajectory)) {
        return trajectory->left_trajectory[GetLength(trajectory)].heading;
    }
    return trajectory->left_trajectory[index].heading;
}

int GetLength(TrajectoryDescription *trajectory) {
    return trajectory->length;
}
}
