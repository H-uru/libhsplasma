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

#ifndef _PFGUIUPDOWNPAIRMOD_H
#define _PFGUIUPDOWNPAIRMOD_H

#include "pfGUIValueCtrl.h"

class PLASMA_DLL pfGUIUpDownPairMod : public pfGUIValueCtrl
{
    CREATABLE(pfGUIUpDownPairMod, kGUIUpDownPairMod, pfGUIValueCtrl)

protected:
    plKey fUpControl, fDownControl;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getUpControl() const { return fUpControl; }
    plKey getDownControl() const { return fDownControl; }

    void setUpControl(plKey ctrl) { fUpControl = std::move(ctrl); }
    void setDownControl(plKey ctrl) { fDownControl = std::move(ctrl); }
};

#endif
