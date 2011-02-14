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

#ifndef _PLSHADOWCASTER_H
#define _PLSHADOWCASTER_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Geometry/plDrawableSpans.h"

class PLASMA_DLL plShadowCaster : public virtual plMultiModifier {
    CREATABLE(plShadowCaster, kShadowCaster, plMultiModifier)

public:
    struct PLASMA_DLL DrawSpan {
    public:
        plDrawableSpans* fDraw;
        plSpan* fSpan;
        unsigned int fIndex;
    };

    enum {
        kNone = 0,
        kSelfShadow = 0x1,
        kPerspective = 0x2,
        kLimitRes = 0x4
    };

protected:
    unsigned char fCastFlags;
    float fBoost, fAttenScale, fBlurScale, fMaxOpacity;
    hsTArray<DrawSpan> fSpans;

public:
    plShadowCaster();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
