#ifndef _PLVIEWFACEMODIFIER_H
#define _PLVIEWFACEMODIFIER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"
#include "Math/hsMatrix44.h"
#include "PRP/Region/hsBounds.h"

DllClass plViewFaceModifier : public plSingleModifier {
    CREATABLE(plViewFaceModifier, kViewFaceModifier, plSingleModifier)

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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsVector3 getScale() const { return fScale; }
    hsVector3 getOffset() const { return fOffset; }
    hsMatrix44 getLocalToParent() const { return fLocalToParent; }
    hsMatrix44 getParentToLocal() const { return fParentToLocal; }
    plKey getFaceObj() const { return fFaceObj; }
    hsBounds3Ext getMaxBounds() const { return fMaxBounds; }

    void setScale(const hsVector3& scale) { fScale = scale; }
    void setOffset(const hsVector3& offset) { fOffset = offset; }
    void setLocalToParent(const hsMatrix44& l2p) { fLocalToParent = l2p; }
    void setParentToLocal(const hsMatrix44& p2l) { fParentToLocal = p2l; }
    void setFaceObj(plKey obj) { fFaceObj = obj; }
    void setMaxBounds(const hsBounds3Ext& bounds) { fMaxBounds = bounds; }
};

#endif
