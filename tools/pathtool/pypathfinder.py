from ctypes import cdll
import ctypes
from collections import namedtuple

"""
Very thin wrapper using ctypes over the pathfinder lib

Check the bottom of this file for exports.
"""

_pathfinder_lib = cdll.LoadLibrary("third_party/pathfinder/pathfinder_cdll.so")

class _Waypoint(ctypes.Structure):
    _fields_ = [("x", ctypes.c_double),
                ("y", ctypes.c_double),
                ("angle", ctypes.c_double)]

    def toPyWaypoint(self):
        return Waypoint(self.x, self.y, self.angle)

    @staticmethod
    def fromPyWaypoint(pyWay):
        return _Waypoint(pyWay.x, pyWay.y, pyWay.angle)

class _Spline(ctypes.Structure):
    _fields_ = [("a", ctypes.c_double),
                ("b", ctypes.c_double),
                ("c", ctypes.c_double),
                ("d", ctypes.c_double),
                ("e", ctypes.c_double),
                ("x_offset", ctypes.c_double),
                ("y_offset", ctypes.c_double),
                ("angle_offset", ctypes.c_double),
                ("knot_distance", ctypes.c_double),
                ("arc_length", ctypes.c_double)]

class _Coord(ctypes.Structure):
    _fields_ = [("x", ctypes.c_double),
                ("y", ctypes.c_double)]

class _Segment(ctypes.Structure):
    _fields_ = [("dt", ctypes.c_double),
                ("x", ctypes.c_double),
                ("y", ctypes.c_double),
                ("position", ctypes.c_double),
                ("velocity", ctypes.c_double),
                ("acceleration", ctypes.c_double),
                ("jerk", ctypes.c_double),
                ("heading", ctypes.c_double)]

    def toPySegment(self):
        return Segment(self.dt, self.x, self.y, self.position, self.velocity,
                       self.acceleration, self.jerk, self.heading)

    @staticmethod
    def fromPySegment(pySeg):
        return _Segment(pySeg.dt, pySeg.x, pySeg.y, pySeg.position,
                        pySeg.velocity, pySeg.acceleration, pySeg.jerk,
                        pySeg.heading)

class _TrajectoryConfig(ctypes.Structure):
    _fields_ = [("dt", ctypes.c_double),
                ("max_v", ctypes.c_double),
                ("max_a", ctypes.c_double),
                ("max_j", ctypes.c_double),
                ("src_v", ctypes.c_double),
                ("src_theat", ctypes.c_double),
                ("dest_pos", ctypes.c_double),
                ("dest_v", ctypes.c_double),
                ("dst_theta", ctypes.c_double),
                ("sample_count", ctypes.c_int)]

class _TrajectoryInfo(ctypes.Structure):
    _fields_ = [("filter1", ctypes.c_int),
                ("filter2", ctypes.c_int),
                ("length", ctypes.c_int),
                ("dt", ctypes.c_double),
                ("u", ctypes.c_double),
                ("v", ctypes.c_double),
                ("impulse", ctypes.c_double)]

class _TrajectoryCandidate(ctypes.Structure):
    _fields_ = [("filter1", ctypes.c_int),
                ("filter2", ctypes.c_int),
                ("length", ctypes.c_int),
                ("dt", ctypes.c_double),
                ("u", ctypes.c_double),
                ("v", ctypes.c_double),
                ("impulse", ctypes.c_double)]

class _TrajectoryCandidate(ctypes.Structure):
    _fields_ = [("saptr", ctypes.POINTER(_Spline)),
                ("laptr", ctypes.POINTER(ctypes.c_double)),
                ("totalLength", ctypes.c_double),
                ("length", ctypes.c_int),
                ("path_length", ctypes.c_int),
                ("info", _TrajectoryInfo),
                ("config", _TrajectoryConfig)]

_pathfinder_lib.pathfinder_prepare.argtypes = (
        ctypes.POINTER(_Waypoint),            # Waypoint *path
        ctypes.c_int,                         # int path_length
        ctypes.c_void_p,                      # void (*fit)(_Waypoint, _Waypoint, Splint*)
        ctypes.c_int,                         # int sample_count
        ctypes.c_double,                      # double dt
        ctypes.c_double,                      # double max_velocity
        ctypes.c_double,                      # double max_acceleration
        ctypes.c_double,                      # max_jerk
        ctypes.POINTER(_TrajectoryCandidate), # TrajectoryCandidate *cand
        )

_pathfinder_lib.pathfinder_generate.argtypes = (
        ctypes.POINTER(_TrajectoryCandidate), # TrajectoryCandidate *c
        ctypes.POINTER(_Segment),             # Segment *segments
        )

_pathfinder_lib.pathfinder_modify_tank.argtypes = (
        ctypes.POINTER(_Segment),   # Segment *original
        ctypes.c_int,               # int length
        ctypes.POINTER(_Segment),   # Segment *left
        ctypes.POINTER(_Segment),   # Segment *right
        ctypes.c_double,            # double wheelbase_width
        )


"""
The input to all of these trajectory generation algorithms is a list
of Waypoint objects.  Behind the scenes, these get converted into _Waypoint
objects which are ctype structs equivalent to the Waypoint struct defined
in pathfinder/structs.h
"""
Waypoint = namedtuple("Waypoint", ["x", "y", "angle"])

"""
The output to all of these trajectory generation algorithms is a list
of Segment objects.  Behind the scenes, these get converted from _Segment
objects which are ctype structs equivalent to the Segment struct defined
in pathfinder/structs.h
"""
Segment = namedtuple("Segment", ["dt", "x", "y", "position", "velocity",
                                 "acceleration", "jerk", "heading"])

def generate_trajectory(waypoints, timestep, max_vel, max_accel, max_jerk):
    """
    Generate a trajectory by calling into the Pathfinder library
    let |waypoints| be a list of Waypoint namedtuple types
    """
    candidate = _TrajectoryCandidate()

    waypoint_buff = (_Waypoint * len(waypoints))()
    for idx, point in enumerate(waypoints):
        waypoint_buff[idx] = _Waypoint.fromPyWaypoint(point)

    _pathfinder_lib.pathfinder_prepare(
            waypoint_buff,
            ctypes.c_int(len(waypoints)),
            _pathfinder_lib.pf_fit_hermite_cubic,
            ctypes.c_int(10000),
            ctypes.c_double(timestep),
            ctypes.c_double(max_vel),
            ctypes.c_double(max_accel),
            ctypes.c_double(max_jerk),
            ctypes.byref(candidate),
    )

    segmentBuff = (_Segment * candidate.length)()

    result = _pathfinder_lib.pathfinder_generate(
            ctypes.byref(candidate),
            segmentBuff,
    )

    return [segment.toPySegment() for segment in segmentBuff]

def generate_tank_trajectory(waypoints, timestep, max_vel,
                             max_accel, max_jerk, wheelbase_width):
    """
    Generate a trajectory for the left and the right wheels
    """
    trajectory = generate_trajectory(
            waypoints=waypoints,
            timestep=timestep,
            max_vel=max_vel,
            max_accel=max_accel,
            max_jerk=max_jerk,
    )

    traj_buff = (_Segment * len(trajectory))()
    for idx, segment in enumerate(trajectory):
        traj_buff[idx] = _Segment.fromPySegment(segment)

    leftBuff = (_Segment * len(trajectory))()
    rightBuff = (_Segment * len(trajectory))()


    _pathfinder_lib.pathfinder_modify_tank(
            traj_buff, ctypes.c_int(len(trajectory)),
            leftBuff,
            rightBuff,
            ctypes.c_double(wheelbase_width),
    )

    return (leftBuff, rightBuff)
