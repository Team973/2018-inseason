"""
Tiny wrapper around libvisualize so that we have something for the local
bazel rule to run as the "main" source file.

Display a visualization of the given json file on a mock field.  Pass
in the location os the .so file for pathfinder.

Invoke with the following command:
    bazel run //src/auto/profiles:visualize_{SPLINE_NAME}
"""

import sys
import tools.pathtool.libvisualize

jsonFile = sys.argv[1]
cdllFile = sys.argv[2]

tools.pathtool.libvisualize.visualize_path(jsonFile, cdllFile)
