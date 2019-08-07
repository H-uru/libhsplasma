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

#ifndef _PFGUILISTBOXMOD_H
#define _PFGUILISTBOXMOD_H

#include "pfGUIControlMod.h"
#include "pfGUISkin.h"

class PLASMA_DLL pfGUIListElement
{
public:
    enum Types { kText, kPicture, kTreeRoot };

private:
    bool fSelected;

public:
    pfGUIListElement() : fSelected() { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    bool isSelected() const { return fSelected; }
    void setSelected(bool sel) { fSelected = sel; }
};


class PLASMA_DLL pfGUIListBoxMod : public pfGUIControlMod
{
    CREATABLE(pfGUIListBoxMod, kGUIListBoxMod, pfGUIControlMod)

public:
    enum ListBoxFlags
    {
        kSingleSelect = kDerivedFlagsStart, kDragAndDropCapable,
        kDisableSelection, kDisableKeyActions, kAllowMultipleElementsPerRow,
        kScrollLeftToRight, kAllowMousePassThrough, kGrowLeavesAndProcessOxygen,
        kHandsOffMultiSelect, kForbidNoSelection
    };

protected:
    plKey fScrollCtrl;

public:
    pfGUIListBoxMod();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getScrollCtrl() const { return fScrollCtrl; }
    void setScrollCtrl(plKey ctrl) { fScrollCtrl = std::move(ctrl); }
};

#endif
