import math

import config

pi = math.acos(-1)

def ik(to):
    angles = []
    x = to[0] - config.kLegRootToJoint1
    y = to[1]

    angles.append(math.atan2(y, x) * 180 / pi)

    x = math.sqrt(x*x + y*y) - config.kLegJoint1ToJoint2
    y = to[2]
    ar = math.atan2(y, x)
    lr2 = x*x + y*y
    lr = math.sqrt(lr2)
    a1 = math.acos((lr2 + config.kLegJoint2ToJoint3*config.kLegJoint2ToJoint3 - config.kLegJoint3ToTip*config.kLegJoint3ToTip)/(2*config.kLegJoint2ToJoint3*lr))
    a2 = math.acos((lr2 - config.kLegJoint2ToJoint3*config.kLegJoint2ToJoint3 + config.kLegJoint3ToTip*config.kLegJoint3ToTip)/(2*config.kLegJoint3ToTip*lr))

    angles.append((ar + a1) * 180 / pi)
    angles.append(90 - ((a1 + a2)  * 180 / pi))

    return angles