#pragma once

#include "base.h"

namespace hexapod {

    enum MovementMode {
        MOVEMENT_STANDBY = 0,

        MOVEMENT_FORWARD,
        MOVEMENT_FORWARDFAST,
        MOVEMENT_BACKWARD,
        MOVEMENT_TURNLEFT,
        MOVEMENT_TURNRIGHT,
        MOVEMENT_SHIFTLEFT,
        MOVEMENT_SHIFTRIGHT,
        MOVEMENT_CLIMB,
        MOVEMENT_ROTATEX,
        MOVEMENT_ROTATEY,
        MOVEMENT_ROTATEZ,
        MOVEMENT_TWIST,

        MOVEMENT_TOTAL,
    };

    inline MovementMode operator++ (MovementMode& m, int) {
        if (m < MOVEMENT_TOTAL)
            m = static_cast<MovementMode>(static_cast<int>(m) + 1);
        return m;
    }

    struct MovementTable {
        const Locations* table;
        int length;
        int stepDuration;
        const int* entries;
        int entriesCount;
    };

    class Movement {
    public:
        Movement(MovementMode mode);

        void setMode(MovementMode newMode);

        const Locations& next(int elapsed);

    private:
        MovementMode mode_;
        Locations position_;
        int index_;             // index in mode position table
        bool transiting_;       // if still in transiting to new mode
        int remainTime_;
    };

}