kLegMountLeftRightX = 29.87
kLegMountOtherX = 22.41
kLegMountOtherY = 55.41

kLegRootToJoint1 = 20.75
kLegJoint1ToJoint2 = 28.0
kLegJoint2ToJoint3 = 42.6
kLegJoint3ToTip = 89.07

SIN30   = 0.5
COS30   = 0.866
SIN45   = 0.7071
COS45   = 0.7071
SIN15   = 0.2588
COS15   = 0.9659

STANDBY_Z = (kLegJoint3ToTip*COS15-kLegJoint2ToJoint3*SIN30)
LEFTRIGHT_X = (kLegMountLeftRightX+kLegRootToJoint1+kLegJoint1ToJoint2+(kLegJoint2ToJoint3*COS30)+kLegJoint3ToTip*SIN15)
OTHER_X = (kLegMountOtherX + (kLegRootToJoint1+kLegJoint1ToJoint2+(kLegJoint2ToJoint3*COS30)+kLegJoint3ToTip*SIN15)*COS45)
OTHER_Y = (kLegMountOtherY + (kLegRootToJoint1+kLegJoint1ToJoint2+(kLegJoint2ToJoint3*COS30)+kLegJoint3ToTip*SIN15)*SIN45)

defaultPosition = (
    (OTHER_X, OTHER_Y, -STANDBY_Z),
    (LEFTRIGHT_X, 0, -STANDBY_Z),
    (OTHER_X, -OTHER_Y, -STANDBY_Z),
    (-OTHER_X, -OTHER_Y, -STANDBY_Z),
    (-LEFTRIGHT_X, 0, -STANDBY_Z),
    (-OTHER_X, OTHER_Y, -STANDBY_Z),
)

mountPosition = (
    (kLegMountOtherX, kLegMountOtherY, 0),
    (kLegMountLeftRightX, 0, 0),
    (kLegMountOtherX, -kLegMountOtherY, 0),
    (-kLegMountOtherX, -kLegMountOtherY, 0),
    (-kLegMountLeftRightX, 0, 0),
    (-kLegMountOtherX, kLegMountOtherY, 0),
)

defaultAngle = (
    -45, 0, 45, 135, 180, 225
)

angleLimitation = (
    (-45, 45),
    (-45, 75),
    (-60, 60),
)
