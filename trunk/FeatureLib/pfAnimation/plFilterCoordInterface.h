#ifndef _PLFILTERCOORDINTERFACE_H
#define _PLFILTERCOORDINTERFACE_H

#include "NucleusLib/pnSceneObject/plCoordinateInterface.h"

DllClass plFilterCoordInterface : public plCoordinateInterface {
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
    virtual ~plFilterCoordInterface();

    DECLARE_CREATABLE(plFilterCoordInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
