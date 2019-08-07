/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLVIEWFACEMODIFIER_H
#define _PLVIEWFACEMODIFIER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"
#include "Math/hsMatrix44.h"
#include "PRP/Region/hsBounds.h"

class PLASMA_DLL plViewFaceModifier : public plSingleModifier
{
    CREATABLE(plViewFaceModifier, kViewFaceModifier, plSingleModifier)

public:
    enum plVFFlags
    {
        kPivotFace, kPivotFavorY, kPivotY, kPivotTumple, kScale, kFaceCam,
        kFaceList, kFacePlay, kFaceObj, kOffset, kOffsetLocal, kMaxBounds
    };

    enum FollowMode
    {
        kFollowCamera, kFollowListener, kFollowPlayer, kFollowObject
    };

protected:
    hsVector3 fScale, fOffset;
    hsMatrix44 fLocalToParent, fParentToLocal;
    plKey fFaceObj;
    hsBounds3Ext fMaxBounds;

public:
    plViewFaceModifier()
    {
        fFlags.setName(kPivotFace, "kPivotFace");
        fFlags.setName(kPivotFavorY, "kPivotFavorY");
        fFlags.setName(kPivotY, "kPivotY");
        fFlags.setName(kPivotTumple, "kPivotTumple");
        fFlags.setName(kScale, "kScale");
        fFlags.setName(kFaceCam, "kFaceCam");
        fFlags.setName(kFaceList, "kFaceList");
        fFlags.setName(kFacePlay, "kFacePlay");
        fFlags.setName(kFaceObj, "kFaceObj");
        fFlags.setName(kOffset, "kOffset");
        fFlags.setName(kOffsetLocal, "kOffsetLocal");
        fFlags.setName(kMaxBounds, "kMaxBounds");
    }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

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
    void setFaceObj(plKey obj) { fFaceObj = std::move(obj); }
    void setMaxBounds(const hsBounds3Ext& bounds) { fMaxBounds = bounds; }
};

#endif
