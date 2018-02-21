import unittest
from pypathfinder import set_cdll_path
import math
from itertools import tee


def pairwise(iterable):
    " s -> (s0, s1), (s1, s2), (s2, s3), ... "
    a, b = tee(iterable)
    next(b, None)
    return zip(a, b)


class TestPyPathfinder(unittest.TestCase):


    def validate_trajectory(self, trajectory, timestep, max_vel, max_accel,
                            max_jerk):
        """
        Given a trajectory, check that it *approximately* obeys the given
        constraints
        """
        for segment in trajectory:
            self.assertAlmostEqual(segment.dt, timestep)
            self.assertLessEqual(segment.velocity, max_vel + 0.1)

        for pre, nxt in pairwise(trajectory):
            expected_d_position = (
                pre.velocity + nxt.velocity) / 2.0 * timestep
            self.assertAlmostEqual(pre.position + expected_d_position,
                                   nxt.position)

    def test_doesnt_crash(self):
        """
        Generate a trajectory using the pathfinder library and run through
        all the points to make sure they nominally satisfy the constraints
        of generation
        """
        Waypoint, Segment, generate_trajectory, generate_tank_trajectory = set_cdll_path()

        trajectory = generate_trajectory([
            Waypoint(x=-4, y=-1, angle=math.radians(45)),
            Waypoint(x=-1, y=2, angle=0),
            Waypoint(x=4, y=20, angle=0),
        ],
            timestep=0.05,
            max_vel=15.0,
            max_accel=10.0,
            max_jerk=60.0,
        )

        self.validate_trajectory(trajectory, 0.05, 15.0, 10.0, 60.0)

    def test_tank_doesnt_crash(self):
        """
        Tank trajectories do not necessarily respect the vel/accel/jerk
        constraints so what I'll do for now is just check that the
        function call doesn't crash
        """
        Waypoint, Segment, generate_trajectory, generate_tank_trajectory = set_cdll_path()

        lTraj, rTraj = generate_tank_trajectory([
            Waypoint(x=-4, y=-1, angle=math.radians(45)),
            Waypoint(x=-1, y=2, angle=0),
            Waypoint(x=4, y=20, angle=0),
        ],
            timestep=0.05,
            max_vel=15.0,
            max_accel=10.0,
            max_jerk=60.0,
            wheelbase_width=24.0,
        )

        for segment in lTraj + rTraj:
            self.assertAlmostEqual(segment.dt, 0.05)


if __name__ == '__main__':
    unittest.main()
