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

#ifndef _PLVOLUMESENSORCONDITIONALOBJECT_H
#define _PLVOLUMESENSORCONDITIONALOBJECT_H

#include "plConditionalObject.h"

class PLASMA_DLL plVolumeSensorConditionalObject : public virtual plConditionalObject {
    CREATABLE(plVolumeSensorConditionalObject,
              kVolumeSensorConditionalObject,
              plConditionalObject)

public:
    enum { kTypeEnter = 0x1, kTypeExit = 0x2 };

protected:
    int fTrigNum, fType;
    bool fFirst, fTriggered, fIgnoreExtraEnters;

public:
    plVolumeSensorConditionalObject() : fTrigNum(-1), fType(kTypeEnter),
                                        fFirst(false), fTriggered(false),
                                        fIgnoreExtraEnters(true) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    int getTrigNum() const { return fTrigNum; }
    int getType() const { return fType; }
    bool getFirst() const { return fFirst; }

    void setTrigNum(int value) { fTrigNum = value; }
    void setType(int value) { fType = value; }
    void setFirst(bool value) { fFirst = value; }
};


class PLASMA_DLL plVolumeSensorConditionalObjectNoArbitration : public virtual plVolumeSensorConditionalObject {
    CREATABLE(plVolumeSensorConditionalObjectNoArbitration,
              kVolumeSensorConditionalObjectNoArbitration,
              plVolumeSensorConditionalObject)
};

#endif
