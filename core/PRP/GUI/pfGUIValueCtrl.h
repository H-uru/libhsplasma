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

#ifndef _PFGUIVALUECTRL_H
#define _PFGUIVALUECTRL_H

#include "pfGUIControlMod.h"

class PLASMA_DLL pfGUIValueCtrl : public pfGUIControlMod
{
    CREATABLE(pfGUIValueCtrl, kGUIValueCtrl, pfGUIControlMod)

protected:
    float fMin, fMax, fStep;

public:
    pfGUIValueCtrl() : fMin(), fMax(), fStep() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getMin() const { return fMin; }
    float getMax() const { return fMax; }
    float getStep() const { return fStep; }

    void setMin(float min) { fMin = min; }
    void setMax(float max) { fMax = max; }
    void setStep(float step) { fStep = step; }
    void setRange(float min, float max) { fMin = min; fMax = max; }
};

#endif
