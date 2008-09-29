#ifndef _PLVIEWFACEMODIFIER_H
#define _PLVIEWFACEMODIFIER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"
#include "Math/hsMatrix44.h"
#include "PRP/Region/hsBounds.h"

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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
