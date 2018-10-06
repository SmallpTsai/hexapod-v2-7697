
from collections import deque
import math

from lib import get_rotate_y_matrix as get_matrix

g_steps = 20

swing_angle = 15
x_radius = 15

def path_generator():
    assert (g_steps % 4) == 0
    quarter = int(g_steps/4)

    pi = math.acos(-1)

    result = []
    step_angle = swing_angle / quarter
    step_offset = x_radius / quarter

    for i in range(quarter):
        m = get_matrix(swing_angle - i*step_angle)
        m[0,3] = -i * step_offset
        result.append(m)

    for i in range(quarter):
        m = get_matrix(-i*step_angle)
        m[0,3] = -x_radius + i * step_offset
        result.append(m)

    for i in range(quarter):
        m = get_matrix(i*step_angle-swing_angle)
        m[0,3] = i * step_offset
        result.append(m)

    for i in range(quarter):
        m = get_matrix(i*step_angle)
        m[0,3] = x_radius-i * step_offset
        result.append(m)

    return result, "matrix", 50, (0, quarter*2)