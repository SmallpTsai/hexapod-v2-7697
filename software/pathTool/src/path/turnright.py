
from collections import deque

from lib import semicircle_generator
from lib import path_rotate_z

g_steps = 20
g_radius = 25

def path_generator():
    assert (g_steps % 4) == 0
    halfsteps = int(g_steps/2)

    path = semicircle_generator(g_radius, g_steps)

    mir_path = deque(path)
    mir_path.rotate(halfsteps)

    return [
        path_rotate_z(path, 45+180), 
        path_rotate_z(mir_path, 0+180), 
        path_rotate_z(path, 315+180), 
        path_rotate_z(mir_path, 225+180), 
        path_rotate_z(path, 180+180), 
        path_rotate_z(mir_path, 135+180), 
    ], "shift", 20, (0, halfsteps)
    