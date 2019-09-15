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

#ifndef _PFGUISKIN_H
#define _PFGUISKIN_H

#include "PRP/KeyedObject/hsKeyedObject.h"

class PLASMA_DLL pfGUISkin : public hsKeyedObject
{
    CREATABLE(pfGUISkin, kGUISkin, hsKeyedObject)

public:
    enum Elements
    {
        kUpLeftCorner, kTopSpan, kUpRightCorner, kRightSpan, kLowerRightCorner,
        kBottomSpan, kLowerLeftCorner, kLeftSpan, kMiddleFill, kSelectedFill,
        kSubMenuArrow, kSelectedSubMenuArrow, kTreeButtonClosed,
        kTreeButtonOpen, kNumElements
    };

    struct PLASMA_DLL pfSRect
    {
        unsigned short fX, fY, fWidth, fHeight;

        pfSRect() : fX(), fY(), fWidth(), fHeight() { }
        void read(hsStream* S);
        void write(hsStream* S);
        void prcWrite(pfPrcHelper* prc);
        void prcParse(const pfPrcTag* tag);
        void clear() { fX = fY = fWidth = fHeight = 0; }
    };

protected:
    plKey fTexture;
    pfSRect fElements[kNumElements];
    unsigned short fItemMargin, fBorderMargin;

public:
    pfGUISkin() : fItemMargin(), fBorderMargin() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const pfSRect& getElement(size_t which) const { return fElements[which]; }
    pfSRect& getElement(size_t which) { return fElements[which]; }

    plKey getTexture() const { return fTexture; }
    unsigned short getItemMargin() const { return fItemMargin; }
    unsigned short getBorderMargin() const { return fBorderMargin; }

    void setTexture(plKey tex) { fTexture = std::move(tex); }
    void setItemMargin(unsigned short margin) { fItemMargin = margin; }
    void setBorderMargin(unsigned short margin) { fBorderMargin = margin; }
};

#endif
