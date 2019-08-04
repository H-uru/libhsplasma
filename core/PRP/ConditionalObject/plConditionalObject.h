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

#ifndef _PLCONDITIONALOBJECT_H
#define _PLCONDITIONALOBJECT_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Util/hsBitVector.h"

class PLASMA_DLL plConditionalObject : public hsKeyedObject
{
    CREATABLE(plConditionalObject, kConditionalObject, hsKeyedObject)

protected:
    bool fSatisfied, fToggle;

public:
    plConditionalObject() : fSatisfied(), fToggle() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    bool getSatisfied() const { return fSatisfied; }
    bool getToggle() const { return fToggle; }

    void setSatisfied(bool value) { fSatisfied = value; }
    void setToggle(bool value) { fToggle = value; }
};


class PLASMA_DLL plPickedConditionalObject : public plConditionalObject
{
    CREATABLE(plPickedConditionalObject, kPickedConditionalObject,
              plConditionalObject)
};


class PLASMA_DLL plPythonFileModConditionalObject : public plConditionalObject
{
    CREATABLE(plPythonFileModConditionalObject,
              kPythonFileModConditionalObject,
              plConditionalObject)
};

#endif
