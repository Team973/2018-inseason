from pypathfinder import generate_tank_trajectory, Waypoint
import math

"""
For now, generate a trajectory using the pypathfinder module
and eyeball it to make sure that the numbers are reasonable
and that it doesn't crash during execution.  Real tests will
come later.
"""

lTraj, rTraj = generate_tank_trajectory([
        Waypoint(x=-4, y=-1, angle=math.radians(45)),
        Waypoint(x=-1, y=2, angle=0),
        Waypoint(x=4, y=2, angle=0),
    ],
    0.1,
    15.0,
    10.0,
    60.0,
    24.0,
)

for idx, segment in enumerate(lTraj):
    print("Segment {:d}:".format(idx))
    print("  (x, y): ({:f}, {:f})".format(segment.x, segment.y))
    print("  Dist: {:f}".format(segment.position))
    print("  Vel: {:f}".format(segment.velocity))
    print("  Accel: {:f}".format(segment.acceleration))
    print("  Jerk: {:f}".format(segment.jerk))
    print("  Heading (rad): {:f}".format(segment.heading))

for idx, (lSeg, rSeg) in enumerate(zip(lTraj, rTraj)):
    print("Seg {:d}: (l: {:f}, r: {:f})".format(idx, lSeg.position, rSeg.position))
