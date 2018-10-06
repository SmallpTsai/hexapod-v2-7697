#pragma once

namespace hexapod { 

    namespace config {
        // all below definition use unit: mm
        const float kLegMountLeftRightX = 29.87;
        const float kLegMountOtherX = 22.41;
        const float kLegMountOtherY = 55.41;
        
        const float kLegRootToJoint1 = 20.75;
        const float kLegJoint1ToJoint2 = 28.0;
        const float kLegJoint2ToJoint3 = 42.6;
        const float kLegJoint3ToTip = 89.07;


        // timing setting. unit: ms
        const int movementInterval = 5;
        const int movementSwitchDuration = 150;
    }

}