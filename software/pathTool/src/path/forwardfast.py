
from collections import deque

from lib import semicircle2_generator

g_steps = 20
y_radius = 50
z_radius = 30
x_radius = 10

def path_generator():
    assert (g_steps % 4) == 0
    halfsteps = int(g_steps/2)

    rpath = semicircle2_generator(g_steps, y_radius, z_radius, x_radius)
    lpath = semicircle2_generator(g_steps, y_radius, z_radius, -x_radius)

    mir_rpath = deque(rpath)
    mir_rpath.rotate(halfsteps)

    mir_lpath = deque(lpath)
    mir_lpath.rotate(halfsteps)

    return [rpath, mir_rpath, rpath, mir_lpath, lpath, mir_lpath, ], "shift", 20, (0, halfsteps)
    