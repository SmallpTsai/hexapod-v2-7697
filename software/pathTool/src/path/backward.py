from collections import deque

from lib import semicircle_generator

g_steps = 20
g_radius = 25

def path_generator():
    assert (g_steps % 4) == 0
    halfsteps = int(g_steps/2)

    path = semicircle_generator(g_radius, g_steps, reverse=True)

    mir_path = deque(path)
    mir_path.rotate(halfsteps)

    return [path, mir_path, path, mir_path, path, mir_path, ], "shift", 20, (0, halfsteps)
