#ifndef _PLSDL_H
#define _PLSDL_H

#include "PRP/plCreatable.h"

namespace plSDL {
    enum ContentsFlags {
        kHasUoid = 0x1,
        kHasNotificationInfo = 0x2,
        kHasTimeStamp = 0x4,
        kSameAsDefault = 0x8,
        kHasDirtyFlag = 0x10,
        kWantTimeStamp = 0x20
    };

    unsigned int VariableLengthRead(hsStream* S, size_t size);
    void VariableLengthWrite(hsStream* S, size_t size, unsigned int value);
};

#endif
