from collections import deque
import math
import numpy as np

pi = math.acos(-1)

def semicircle_generator(radius, steps, reverse=False):
    assert (steps % 4) == 0
    halfsteps = int(steps/2)

    step_angle = pi / halfsteps

    result = []

    # first half, move backward (only y change)
    for i in range(halfsteps):
        result.append((0, radius - i*radius*2/(halfsteps), 0))

    # second half, move forward in semicircle shape (y, z change)
    for i in range(halfsteps):
        angle = pi - step_angle*i
        y = radius * math.cos(angle)
        z = radius * math.sin(angle)
        result.append((0, y, z))

    result = deque(result)
    result.rotate(int(steps/4))

    if reverse:
        result = deque(reversed(result))
        result.rotate(1)

    return result

def semicircle2_generator(steps, y_radius, z_radius, x_radius, reverse=False):
    assert (steps % 4) == 0
    halfsteps = int(steps/2)

    step_angle = pi / halfsteps

    result = []

    # first half, move backward (only y change)
    for i in range(halfsteps):
        result.append((0, y_radius - i*y_radius*2/(halfsteps), 0))

    # second half, move forward in semicircle shape (y, z change)
    for i in range(halfsteps):
        angle = pi - step_angle*i
        y = y_radius * math.cos(angle)
        z = z_radius * math.sin(angle)
        x = x_radius * math.sin(angle)
        result.append((x, y, z))

    result = deque(result)
    result.rotate(int(steps/4))

    if reverse:
        result = deque(reversed(result))
        result.rotate(1)

    return result

def get_rotate_x_matrix(angle):
    angle = angle * pi / 180
    return np.matrix([
        [1, 0, 0, 0],
        [0, math.cos(angle), -math.sin(angle), 0],
        [0, math.sin(angle), math.cos(angle), 0],
        [0, 0, 0, 1],
    ])

def get_rotate_y_matrix(angle):
    angle = angle * pi / 180
    return np.matrix([
        [math.cos(angle), 0, math.sin(angle), 0],
        [0, 1, 0, 0],
        [-math.sin(angle), 0, math.cos(angle), 0],
        [0, 0, 0, 1],
    ])

def get_rotate_z_matrix(angle):
    angle = angle * pi / 180
    return np.matrix([
        [math.cos(angle), -math.sin(angle), 0, 0],
        [math.sin(angle), math.cos(angle), 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1],
    ])

def matrix_mul(m, pt):
    ptx = list(pt) + [1]
    return list((m * np.matrix(ptx).T).T.flat)[:-1]

def point_rotate_x(pt, angle):
    ptx = list(pt) + [1]
    return list((get_rotate_x_matrix(angle) * np.matrix(ptx).T).T.flat)[:-1]

def point_rotate_y(pt, angle):
    ptx = list(pt) + [1]
    return list((get_rotate_y_matrix(angle) * np.matrix(ptx).T).T.flat)[:-1]

def point_rotate_z(pt, angle):
    ptx = list(pt) + [1]
    return list((get_rotate_z_matrix(angle) * np.matrix(ptx).T).T.flat)[:-1]

def path_rotate_x(path, angle):
    return [point_rotate_x(p, angle) for p in path]

def path_rotate_y(path, angle):
    return [point_rotate_y(p, angle) for p in path]

def path_rotate_z(path, angle):
    return [point_rotate_z(p, angle) for p in path]

if __name__ == '__main__':
    pt = [0, 1, 0]
    print(point_rotate_z(pt, 270))