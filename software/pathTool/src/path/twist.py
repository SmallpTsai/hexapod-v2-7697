
from collections import deque
import math

from lib import get_rotate_x_matrix, get_rotate_z_matrix

g_steps = 20

raise_angle = 3
twist_x_angle = 20
twise_y_angle = 12

def path_generator():
    assert (g_steps % 4) == 0

    result = []

    quarter = int(g_steps / 4)
    step_x_angle = twist_x_angle / quarter
    step_y_angle = twise_y_angle / quarter

    m = get_rotate_x_matrix(raise_angle)
    for i in range(quarter):
        result.append(m * get_rotate_z_matrix(i*step_x_angle) * get_rotate_x_matrix(i*step_y_angle))

    for i in range(quarter):
        result.append(m * get_rotate_z_matrix((quarter-i)*step_x_angle) * get_rotate_x_matrix((quarter-i)*step_y_angle))

    for i in range(quarter):
        result.append(m * get_rotate_z_matrix(-i*step_x_angle) * get_rotate_x_matrix(i*step_y_angle))

    for i in range(quarter):
        result.append(m * get_rotate_z_matrix((-quarter+i)*step_x_angle) * get_rotate_x_matrix((quarter-i)*step_y_angle))

    return result, "matrix", 50, [0, 10]