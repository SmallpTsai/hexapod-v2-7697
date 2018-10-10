
from collections import deque

from lib import semicircle_generator
from lib import path_rotate_z

g_steps = 20
g_radius = 25

def path_generator():
    assert (g_steps % 4) == 0
    halfsteps = int(g_steps/2)

    path = semicircle_generator(g_radius, g_steps)
    path = path_rotate_z(path, 90)  # shift 90 degree to make the path "left" shift

    mir_path = deque(path)
    mir_path.rotate(halfsteps)

    return [path, mir_path, path, mir_path, path, mir_path, ], "shift", 20, (0, halfsteps)
