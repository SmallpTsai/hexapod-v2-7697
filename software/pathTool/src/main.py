import argparse
import logging
import os
import sys

import config
import kinematics
from path.lib import point_rotate_z, matrix_mul

def collectPath(sub_folder):
    scripts = {}
    for script_name in [f[:-3] for f in sorted(os.listdir(sub_folder)) if f.endswith('.py') and os.path.isfile(os.path.join(sub_folder, f))]:
        module = __import__(script_name)
        if not hasattr(module, 'path_generator'):
            continue
        scripts[script_name] = module.path_generator

    return scripts

def show_detail(path, result):
    print("path:{}:".format(path))
    for i, p in enumerate(result):
        print("{:2d}  {:5.2f}, {:5.2f}, {:5.2f}".format(i, p[0], p[1], p[2]))

def verify_points(pt):
    angles = kinematics.ik(pt)

    ok = True
    failed = []
    for i, angle in enumerate(angles):
        if angle < config.angleLimitation[i][0] or angle > config.angleLimitation[i][1]:
            ok = False
            failed.append((i, angle))

    return ok, failed

def verify_path(path, params):
    data, mode, _, _ = params
    print("Verifying {}...".format(path))

    all_ok = True
    if mode == "shift":
        # data: float[6][N][3]
        assert(len(data) == 6)

        for i in range(len(data[0])):
            for j in range(6):
                pt = [config.defaultPosition[j][k] - config.mountPosition[j][k] + data[j][i][k] for k in range(3)]
                pt = point_rotate_z(pt, config.defaultAngle[j])
                ok, failed = verify_points(pt)

                if not ok:
                    print("{}, {} failed: {}".format(i, j, failed))
                    all_ok = False

    elif mode == "matrix":
        # data: np.matrix[N]
        for i in range(len(data)):
            for j in range(6):
                pt = matrix_mul(data[i], config.defaultPosition[j])
                for k in range(3):
                    pt[k] -= config.mountPosition[j][k]
                pt = point_rotate_z(pt, config.defaultAngle[j])

                ok, failed = verify_points(pt)

                if not ok:
                    print("{}, {} failed: {}".format(i, j, failed))
                    all_ok = False
    
    return all_ok


def generate_c_body(path, params):
    data, mode, dur, entries = params
    result = "\nconst Locations {}_paths[] {{\n".format(path)

    if mode == "shift":
        # data: float[6][N][3]

        assert(len(data) == 6)

        count = len(data[0])
        for i in range(count):
            result += "    {" + ", ".join(
                "{{P{idx}X+({x:.2f}), P{idx}Y+({y:.2f}), P{idx}Z+({z:.2f})}}".format(x=data[j][i][0], y=data[j][i][1], z=data[j][i][2], idx=j+1) 
                for j in range(6)
            ) + "},\n"

    elif mode == "matrix":
        # data: np.matrix[N]

        count = len(data)
        for i in range(count):
            result += "    {" + ", \n     ".join(
                "{{P{idx}X*{e00:.2f} + P{idx}Y*{e01:.2f} + P{idx}Z*{e02:.2f} + {e03:.2f}, P{idx}X*{e10:.2f} + P{idx}Y*{e11:.2f} + P{idx}Z*{e12:.2f} + {e13:.2f}, P{idx}X*{e20:.2f} + P{idx}Y*{e21:.2f} + P{idx}Z*{e22:.2f} + {e23:.2f}}}".format(
                    e00=data[i].item((0,0)), e01=data[i].item((0,1)), e02=data[i].item((0,2)), e03=data[i].item((0,3)),
                    e10=data[i].item((1,0)), e11=data[i].item((1,1)), e12=data[i].item((1,2)), e13=data[i].item((1,3)),
                    e20=data[i].item((2,0)), e21=data[i].item((2,1)), e22=data[i].item((2,2)), e23=data[i].item((2,3)),
                    idx=j+1) 
                for j in range(6)
            ) + "},\n"

    else:
        raise RuntimeError("Generation mode: {} not supported".format(mode))

    result += "};\n"
    result += "const int {}_entries[] {{ {} }};\n".format(path, ",".join(str(e) for e in entries))
    result += "const MovementTable {name}_table {{{name}_paths, {count}, {dur}, {name}_entries, {ecount} }};".format(name=path, count=count, dur=dur, ecount=len(entries))
    return result

def generate_c_def(path):
    return """const MovementTable& {name}Table() {{
    return {name}_table;
}}""".format(name=path)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='pathTool: generate Hexapod path')
    parser.add_argument('--pathDir', metavar='DIR',  dest='path_dir', default='path',
                        help='path script directory (default: {})'.format('path'))
    parser.add_argument('--outPath', metavar='PATH',  dest='out_path', default='output/movement_table.h',
                        help='path script directory (default: {})'.format('output/movement_table.h'))
    args = parser.parse_args()

    sys.path.insert(0, args.path_dir)

    # find available path generator
    paths = collectPath(args.path_dir)

    # generate all paths
    results = {path: generator() for path, generator in paths.items()}

    # verify all path is within safe angles
    
    verified = [1 for path, data in results.items() if not verify_path(path, data)]
    if len(verified) > 0:
        print("There were errors, exit...")
    else:
        # output results
        with open(args.out_path, "w") as f:
            print("//", file=f)
            print("// This file is generated, dont directly modify content...", file=f)
            print("//", file=f)
            print("namespace {", file=f)
            for path, data in results.items():
                print(generate_c_body(path, data), file=f)
            print("}\n", file=f)
            for path in results:
                print(generate_c_def(path), file=f)

        print("Result written to {}".format(args.out_path))


