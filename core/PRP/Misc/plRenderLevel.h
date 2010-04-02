#ifndef _PLRENDERLEVEL_H
#define _PLRENDERLEVEL_H

#include "PlasmaDefs.h"

namespace plRenderLevel {
    enum {
        kOpaqueMajorLevel = 0x0,
        kFBMajorLevel = 0x1,
        kDefRendMajorLevel = 0x2,
        kBlendRendMajorLevel = 0x4,
        kLateRendMajorLevel = 0x8
    };

    enum { kMajorShift = 0x1C };

    enum {
        kDefRendMinorLevel = 0x0,
        kOpaqueMinorLevel = 0x0,
        kMinorLevelMask = 0x0FFFFFFF,
        kAvatarRendMinorLevel = 0x0FFFFFFE
    };
};

#endif
