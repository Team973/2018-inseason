import sys, json, pypathfinder

sourcePath = sys.argv[1]
targetPath = sys.argv[2]

def openPointStructs(source):
    input = json.load(source)
    left, right = generate_tank_trajectory(input["waypoints"], input["timestep"],
                                      input["max_vel"], input["max_accel"],
                                      input["max_jerk"])
    return left, right

def writeHeader(target):
    header = open(target, "w+")
    leftTraj, rightTraj = openPointStructs(sourcePath))
    header.write('''#include "path_to_pathfinder_struct_definitions.h"
    namespace generated_profiles {
    TrajectoryDescription ''' + input[name])
    header.write("{\n" +
    ".timestep = " + input["timestep"] +
    ", .max_vel = " + input["max_vel"] +
    ", .max_accel = " + input["waypoints"] +
    ", .max_jerk = " + input["max_jerk"] +
    ", .wheelbase_width = " + input["wheelbase_width"] +
    ", .length = 300\n"
    ", .left_trajectory = {" + leftTraj +
    ", .right_trajectory = {" + rightTraj +
    "};
    }")
    header.close()

writeHeader(targetPath)
