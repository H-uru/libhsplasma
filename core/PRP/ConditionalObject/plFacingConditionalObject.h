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

#ifndef _PLFACINGCONDITIONALOBJECT_H
#define _PLFACINGCONDITIONALOBJECT_H

#include "plConditionalObject.h"

class PLASMA_DLL plFacingConditionalObject : public plConditionalObject
{
    CREATABLE(plFacingConditionalObject, kFacingConditionalObject,
              plConditionalObject)

protected:
    float fTolerance;
    bool fDirectional;

public:
    plFacingConditionalObject() : fTolerance(), fDirectional() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getTolerance() const { return fTolerance; }
    bool getDirectional() const { return fDirectional; }

    void setTolerance(float value) { fTolerance = value; }
    void setDirectional(bool value) { fDirectional = value; }
};

#endif
