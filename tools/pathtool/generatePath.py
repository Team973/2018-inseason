import sys, json
from pypathfinder import set_cdll_path

jsonPath = sys.argv[1]
headerPath = sys.argv[2]
cdllPath = sys.argv[3]

Waypoint, Segment, generate_trajectory, generate_tank_trajectory = set_cdll_path(cdllPath)

def openPointStructs(source):
    with open(source) as inputFile:
        sourceJSON = json.load(inputFile)
        waypoints = []
        for waypoint in sourceJSON["waypoints"]:
            waypoints.append(Waypoint(x = waypoint["x"], y = waypoint["y"], angle = waypoint["angle"]))
        left, right = generate_tank_trajectory(waypoints, sourceJSON["timestep"],
                sourceJSON["max_vel"], sourceJSON["max_accel"],
                sourceJSON["max_jerk"], sourceJSON["wheelbase_width"])
        return left, right, sourceJSON

def writeHeader(target):
    header = open(target, "w+")
    leftTraj, rightTraj, sourceJSON = openPointStructs(jsonPath)
    header.write('''#include "lib/trajectories/structs.h"

using namespace trajectories;

namespace generated_profiles {

Segment leftTrajectory[] = {\n''')
    printSegments(leftTraj, header)
    header.write("Segment rightTrajectory[] = {\n")
    printSegments(rightTraj, header)
    header.write('''TrajectoryDescription {} {{
        .timestep = {},
        .max_vel = {},
        .max_accel = {},
        .max_jerk = {},
        .wheelbase_width = {},
        .length = {},
        .left_trajectory = leftTrajectory,
        .right_trajectory = rightTrajectory
            }};
        }}'''.format(sourceJSON["name"], sourceJSON["timestep"], sourceJSON["max_vel"], sourceJSON["max_accel"],
                sourceJSON["max_jerk"], sourceJSON["wheelbase_width"], len(leftTraj)))
    header.close()

def printSegments(trajectory, file):
    for count, segment in enumerate(trajectory):
        file.write("        {.dt=" + str(segment.dt) + ", .x=" + str(segment.x) + ", .y=" + str(segment.y)
                     + ", .position=" + str(segment.position) + ", .velocity=" + str(segment.velocity)
                     + ", .acceleration=" + str(segment.acceleration) + ", .jerk=" + str(segment.jerk)
                     + ", .heading=" + str(segment.heading) + "}")
        if count < len(trajectory) - 1:
            file.write(",\n")
    file.write("\n};\n")

writeHeader(headerPath)
