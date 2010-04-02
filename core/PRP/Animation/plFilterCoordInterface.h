#ifndef _PLFILTERCOORDINTERFACE_H
#define _PLFILTERCOORDINTERFACE_H

#include "PRP/Object/plCoordinateInterface.h"

DllClass plFilterCoordInterface : public plCoordinateInterface {
    CREATABLE(plFilterCoordInterface, kFilterCoordInterface,
              plCoordinateInterface)

public:
    enum {
        kNoRotation = 0x1,
        kNoTransX = 0x2,
        kNoTransY = 0x4,
        kNoTransZ = 0x8,
        kNoMove = kNoTransX | kNoTransY | kNoTransZ,
        kNoNothing = kNoMove | kNoRotation
    };

protected:
    unsigned int fFilterMask;
    hsMatrix44 fRefParentLocalToWorld;

public:
    plFilterCoordInterface();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
