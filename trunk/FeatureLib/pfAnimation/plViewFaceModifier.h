#ifndef _PLVIEWFACEMODIFIER_H
#define _PLVIEWFACEMODIFIER_H

#include "NucleusLib/pnModifier/plModifier.h"
#include "CoreLib/hsGeometry3.h"
#include "CoreLib/hsMatrix44.h"
#include "CoreLib/hsBounds.h"

DllClass plViewFaceModifier : public plSingleModifier {
public:
    enum plVFFlags {
        kPivotFace, kPivotFavorY, kPivotY, kPivotTumple, kScale, kFaceCam,
        kFaceList, kFacePlay, kFaceObj, kOffset, kOffsetLocal, kMaxBounds
    };

    enum FollowMode {
        kFollowCamera, kFollowListener, kFollowPlayer, kFollowObject
    };

protected:
    hsVector3 fLastDirY, fScale;
    hsMatrix44 fLocalToParent, fParentToLocal;
    hsPoint3 fFacePoint;
    plKey fFaceObj;
    hsVector3 fOffset;
    hsBounds3Ext fMaxBounds;

public:
    plViewFaceModifier();
    virtual ~plViewFaceModifier();

    DECLARE_CREATABLE(plViewFaceModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
