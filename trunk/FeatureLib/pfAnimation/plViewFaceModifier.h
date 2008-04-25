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
    hsVector3 fScale, fOffset;
    hsMatrix44 fLocalToParent, fParentToLocal;
    plKey fFaceObj;
    hsBounds3Ext fMaxBounds;

public:
    plViewFaceModifier();
    virtual ~plViewFaceModifier();

    DECLARE_CREATABLE(plViewFaceModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
