
from collections import deque
import math

from lib import get_rotate_x_matrix, get_rotate_y_matrix

g_steps = 20

z_lift = 4.5
xy_radius = 1

def path_generator():

    pi = math.acos(-1)

    result = []
    step_angle = 2*pi / g_steps
    for i in range(g_steps):
        x = xy_radius * math.cos(i*step_angle)
        y = xy_radius * math.sin(i*step_angle)

        m = get_rotate_y_matrix(math.atan2(x, z_lift)*180/pi) * get_rotate_x_matrix(math.atan2(y, z_lift)*180/pi)
        result.append(m)

    return result, "matrix", 50, range(g_steps)