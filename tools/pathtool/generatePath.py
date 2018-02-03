import sys, json
import pypathfinder

sourcePath = sys.argv[1]
targetPath = sys.argv[2]

def openPointStructs(source):
    with open(source) as inputFile:
         sourceJSON = json.load(source)
    left, right = generate_tank_trajectory(sourceJSON["waypoints"], sourceJSON["timestep"],
                                      sourceJSON["max_vel"], sourceJSON["max_accel"],
                                      sourceJSON["max_jerk"])
    return left, right, sourceJSON

def writeHeader(target):
    header = open(target, "w+")
    leftTraj, rightTraj, sourceJSON = openPointStructs(sourcePath)
    header.write('''#include "path_to_pathfinder_struct_definitions.h"
    namespace generated_profiles {
    TrajectoryDescription ''' + sourceJSON[name])
    header.write("""{
    .timestep = {0}
    , .max_vel = {1}
    , .max_accel = {2}
    , .max_jerk =   {3}
    , .wheelbase_width = {4}
    , .length = {5}
    , .left_trajectory = { {6}
    , .right_trajectory = { {7}
    };
    }""".format(sourceJSON["timestep"], sourceJSON["max_vel"], sourceJSON["waypoints"],
                sourceJSON["max_jerk"], sourceJSON["wheelbase_width"], len(leftTraj),
                leftTraj, rightTraj))
    header.close()

writeHeader(targetPath)
