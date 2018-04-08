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
import math
from pypathfinder import parse_spline_file

def writeHeader(jsonPath, target, cdllPath):
    """
    Write the C++ header file containing the generated spline
    """
    header = open(target, "w+")
    with open(target, "w+") as header:
        leftTraj, rightTraj, waypoints, sourceJSON = parse_spline_file(jsonPath, cdllPath)
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
            ("    {{.dt={}, .x={}, .y={}, .position={}, \n"
             "      .velocity={}, .acceleration={}, .jerk={}, \n"
             "      .heading={}, .angular_rate={}, .angular_accel={}}}"
            ).format(segment.dt, segment.x, segment.y,
                     segment.position, segment.velocity,
                     segment.acceleration, segment.jerk,
                     segment.heading, segment.angular_rate,
                     segment.angular_accel))
        if count < len(trajectory) - 1:
            outfile.write(",\n")
    outfile.write("\n};\n")

if __name__ == '__main__':
    jsonPath = sys.argv[1]
    headerPath = sys.argv[2]
    cdllPath = sys.argv[3]

    writeHeader(jsonPath, headerPath, cdllPath)
    print(headerPath)
