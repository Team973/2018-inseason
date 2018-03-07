"""
Generate a visualization of the given path on a regulation frc field
"""

import sys
import math
import json
from itertools import tee
from PIL import Image, ImageDraw
from tools.pathtool.pypathfinder import set_cdll_path

PX_PER_INCH = 8
FIELD_WIDTH = 54 * 12 // 2
FIELD_HEIGHT = 27 * 12
FIELD_SIZE_PX = (FIELD_WIDTH * PX_PER_INCH,
                 FIELD_HEIGHT * PX_PER_INCH)

def visualize_path(pathfile, cdllPath):
    """
    Grab the path descriptor at |pathfile| and create a visualization
    of it to display to the user
    """
    img = _create_field_img()
    _draw_field(img)
    waypoints, offset, wheelbase_width, lTraj, rTraj = _gen_path(pathfile, cdllPath)
    _draw_path(img, waypoints, offset, wheelbase_width, lTraj, rTraj)
    _img_show_and_wait(img)

def _create_field_img():
    """
    Create an empty image that is the size of the field
    """
    img = Image.new('RGB', FIELD_SIZE_PX, color=(255, 255, 255))
    return img

def _draw_line(img, cursor, pt1, pt2, color=(0, 0, 0)):
    """
    Draw a line from pt1 to pt2 where axes are in inches
    Force (0, 0) to be the bottom left of the screen
    """
    pt1 = (pt1[0], FIELD_HEIGHT - pt1[1])
    pt2 = (pt2[0], FIELD_HEIGHT - pt2[1])
    line = pt1 + pt2
    line = tuple([x * PX_PER_INCH for x in line])
    cursor.line(line, fill=color, width=4)

def _draw_rect(img, cursor, pt1, pt2, fill):
    """
    Draw a rectangle bound by topleft, bottomright where axes are in inches
    Force (0, 0) to be the bottom left of the screen
    """
    pt1 = (pt1[0], FIELD_HEIGHT - pt1[1])
    pt2 = (pt2[0], FIELD_HEIGHT - pt2[1])
    line = pt1 + pt2
    line = tuple([x * PX_PER_INCH for x in line])
    cursor.rectangle(line, fill=fill)

def _draw_field(img):
    """
    Draw the 2018 competition field on the given image
    Currently only draws the left half
    """
    cursor = ImageDraw.Draw(img)

    # Corners against alliance wall
    corner_offset = 35.563
    _draw_line(img, cursor,
               (0, corner_offset),
               (corner_offset, 0))
    _draw_line(img, cursor,
               (0, FIELD_HEIGHT - corner_offset),
               (corner_offset, FIELD_HEIGHT))

    # Auto line
    _draw_line(img, cursor, (120, 0), (120, FIELD_HEIGHT))

    # Switch
    _draw_rect(img, cursor, (139.813, 85.5), (195.563, 238.750),
               fill=(115, 115, 115))

    # Switch scoring regions
    _draw_rect(img, cursor, (139.813, 85.5), (195.563, 125.742),
               fill=(0, 255, 0))
    _draw_rect(img, cursor, (139.813, 198.266), (195.563, 238.750),
               fill=(0, 255, 0))

    # Ramp
    _draw_rect(img, cursor, (261.059, 97.189), (FIELD_WIDTH, 226.000),
               fill=(255, 255, 181))

    # Null territories
    _draw_rect(img, cursor, (287.563, 0), (FIELD_WIDTH, 97.189),
               fill=(190, 190, 190))
    _draw_rect(img, cursor, (287.563, 226.000), (FIELD_WIDTH, FIELD_HEIGHT),
               fill=(190, 190, 190))

    # Scale scoring platforms
    scale_height = 36.188
    _draw_rect(img, cursor, (299.211, 71.562), (347.915, 107.750),
               fill=(0, 255, 0))
    _draw_rect(img, cursor, (299.211, 215.977), (347.915, 252.165),
               fill=(0, 255, 0))

    # Cubes
    for cube_offset in [85.5, 113.6, 141.45, 169.8, 198.266, 226.0]:
        cube_width = 208.313 - 195.813
        topleft = (195.813, cube_offset)
        bottomright = (208.313, cube_offset + cube_width)
        _draw_rect(img, cursor, topleft, bottomright, fill=(255, 255, 0))

def _gen_path(pathfile, cdllPath):
    """
    Generate a trajectory based on the given json file
    and grab some settings for how to visualize it

    Visual_{x,y}_offset are settings in the json file that the user can
    use to shift the spline around on fieldspace.
    """
    Waypoint, _, _, generate_tank_trajectory = set_cdll_path(cdllPath)

    with open(pathfile) as inputFile:
        sourceJSON = json.load(inputFile)
        waypoints = []
        for waypoint in sourceJSON["waypoints"]:
            waypoints.append(
                Waypoint(x=waypoint["x"], y=waypoint["y"],
                         angle=(math.pi / 180.0) * waypoint["angle"])
            )

        lTraj, rTraj = generate_tank_trajectory(
            waypoints, sourceJSON["timestep"],
            sourceJSON["max_vel"], sourceJSON["max_accel"],
            sourceJSON["max_jerk"], sourceJSON["wheelbase_width"],
            reverse=sourceJSON.get('reverse', False))

        x_offset = sourceJSON.get('visual_x_offset', 0)
        y_offset = sourceJSON.get('visual_y_offset', 0)

    return (
        waypoints,
        (x_offset, y_offset),
        sourceJSON["wheelbase_width"],
        lTraj, rTraj
    )

def _pairwise(iterable):
    " s -> (s0, s1), (s1, s2), (s2, s3), ... "
    a, b = tee(iterable)
    next(b, None)
    return zip(a, b)

def _draw_path(img, waypoints, offset, wheelbase_width, lTraj, rTraj):
    """
    Draw the given path.
    Note that image coordinates start in the top-left while our standard
    is for the coordinates to start in the bottom-left.
    """
    x_offset, y_offset = offset

    cursor = ImageDraw.Draw(img)
    for pointA, pointB in _pairwise(lTraj):
        _draw_line(img, cursor,
                   (pointA.x + x_offset, FIELD_HEIGHT - pointA.y - y_offset),
                   (pointB.x + x_offset, FIELD_HEIGHT - pointB.y - y_offset),
                   color=(255, 0, 255))

    for pointA, pointB in _pairwise(rTraj):
        _draw_line(img, cursor,
                   (pointA.x + x_offset, FIELD_HEIGHT - pointA.y - y_offset),
                   (pointB.x + x_offset, FIELD_HEIGHT - pointB.y - y_offset),
                   color=(255, 0, 255))

    for waypoint in waypoints:
        left_wheel = (
            waypoint.x + x_offset + (
                wheelbase_width / 2 *
                math.cos(waypoint.angle + math.pi / 2)
            ),
            FIELD_HEIGHT - waypoint.y - y_offset + (
                wheelbase_width / 2 *
                math.sin(waypoint.angle + math.pi / 2)
            )
        )
        right_wheel = (
            waypoint.x + x_offset + (
                wheelbase_width / 2 *
                math.cos(waypoint.angle - math.pi / 2)
            ),
            FIELD_HEIGHT - waypoint.y - y_offset + (
                wheelbase_width / 2 *
                math.sin(waypoint.angle - math.pi / 2)
            )
        )

        _draw_line(img, cursor, left_wheel, right_wheel, color=(255, 0, 255))

def _img_show_and_wait(img):
    """
    Output the image.  Currently we ues matplotlib because it's portable
    and provides some nice features (like labeling axes and letting the
    user mouse over the image)
    """
    import matplotlib.pyplot as plt
    import matplotlib.image as mpimg
    img.save('tmp.png')
    img = mpimg.imread('tmp.png')
    imgplot = plt.imshow(img,
                         origin='lower',
                         extent=(0, FIELD_WIDTH, 0, FIELD_HEIGHT))
    plt.xlabel('X coordinate (in inches)')
    plt.ylabel('Y coordinate (in inches)')
    plt.show()

if __name__ == '__main__':
    jsonFile = sys.argv[1]
    cdllFile = sys.argv[2]

    visualize_path(jsonFile, cdllFile)
