
from collections import deque

from lib import semicircle2_generator

g_steps = 20
y_radius = 20
z_radius = 80
x_radius = 30

z_shift = -30

def path_generator():
    assert (g_steps % 4) == 0
    halfsteps = int(g_steps/2)

    rpath = [(x, y, z + z_shift) for x, y, z in semicircle2_generator(g_steps, y_radius, z_radius, x_radius)]
    lpath = [(x, y, z + z_shift) for x, y, z in semicircle2_generator(g_steps, y_radius, z_radius, -x_radius)]

    mir_rpath = deque(rpath)
    mir_rpath.rotate(halfsteps)

    mir_lpath = deque(lpath)
    mir_lpath.rotate(halfsteps)

    return [rpath, mir_rpath, rpath, mir_lpath, lpath, mir_lpath, ], "shift", 30, (0, halfsteps)
    