#include "hsGDeviceRef.h"

hsGDeviceRef::hsGDeviceRef() : flags(kNone), useTime(0) { }

bool hsGDeviceRef::IsDirty() {
    return (flags & kDirty);
}

void hsGDeviceRef::SetDirty(bool dirty) {
    if (dirty)
        flags |= kDirty;
    else
        flags &= ~kDirty;
}
