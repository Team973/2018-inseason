"""
Generate a .h file declaring and inline-initializing all the segments
in a spline path.
Arg 1: JSON file describing the path to be generated
Arg 2: Destination file to write to (C++ header file)
Arg 3: path to the pathfinder shared library
"""

import sys
import json
import textwrap
from pypathfinder import set_cdll_path

jsonPath = sys.argv[1]
headerPath = sys.argv[2]
cdllPath = sys.argv[3]

Waypoint, Segment, generate_trajectory, generate_tank_trajectory = set_cdll_path(cdllPath)

def openPointStructs(source):
    """
    Read in the spline description file and generate the waypoints
    described by that file
    """
    with open(source) as inputFile:
        sourceJSON = json.load(inputFile)
        waypoints = []
        for waypoint in sourceJSON["waypoints"]:
            waypoints.append(
                Waypoint(x=waypoint["x"], y=waypoint["y"],
                         angle=waypoint["angle"])
            )

        left, right = generate_tank_trajectory(
            waypoints, sourceJSON["timestep"],
            sourceJSON["max_vel"], sourceJSON["max_accel"],
            sourceJSON["max_jerk"], sourceJSON["wheelbase_width"],
            reverse=sourceJSON.get('reverse', False))

        return left, right, sourceJSON

def writeHeader(target):
    """
    Write the C++ header file containing the generated spline
    """
    header = open(target, "w+")
    with open(target, "w+") as header:
        leftTraj, rightTraj, sourceJSON = openPointStructs(jsonPath)
        header.write(textwrap.dedent("""\
            #pragma once

            #include "lib/trajectories/structs.h"

            using namespace trajectories;

            namespace {} {{

            """.format(sourceJSON["name"])))

        printSegments("leftTrajectory", leftTraj, header)

        header.write("\n")
        printSegments("rightTrajectory", rightTraj, header)

        header.write(textwrap.dedent("""\

            static TrajectoryDescription {} {{
                .timestep = {},
                .max_vel = {},
                .max_accel = {},
                .max_jerk = {},
                .wheelbase_width = {},
                .length = {},
                .left_trajectory = leftTrajectory,
                .right_trajectory = rightTrajectory
            }};

            }}
            """.format(sourceJSON["name"], sourceJSON["timestep"],
                       sourceJSON["max_vel"], sourceJSON["max_accel"],
                       sourceJSON["max_jerk"], sourceJSON["wheelbase_width"],
                       len(leftTraj))))

def printSegments(varname, trajectory, outfile):
    """
    Output a single segment array given a name, a list of segments,
    and the file to write to
    """
    outfile.write("static Segment {}[] = {{\n".format(varname))
    for count, segment in enumerate(trajectory):
        outfile.write(
            ("    {{.dt={}, .x={}, .y={}, .position={}, "
             ".velocity={}, .acceleration={}, .jerk={}, "
             ".heading={}}}"
            ).format(segment.dt, segment.x, segment.y,
                     segment.position, segment.velocity,
                     segment.acceleration, segment.jerk,
                     segment.heading))
        if count < len(trajectory) - 1:
            outfile.write(",\n")
    outfile.write("\n};\n")

writeHeader(headerPath)
print(headerPath)
