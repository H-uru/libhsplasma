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

#ifndef _PLMODIFIER_H
#define _PLMODIFIER_H

#include "PRP/Object/plSynchedObject.h"
#include "PRP/Object/plSceneObject.h"
#include "Util/hsBitVector.h"

DllClass plModifier : public virtual plSynchedObject {
    CREATABLE(plModifier, kModifier, plSynchedObject)
};


DllClass plSingleModifier : public virtual plModifier {
    CREATABLE(plSingleModifier, kSingleModifier, plModifier)

protected:
    hsBitVector fFlags;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getFlag(size_t flag) const { return fFlags.get(flag); }
    void setFlag(size_t flag, bool value) { fFlags.set(flag, value); }
};


DllClass plMultiModifier : public virtual plModifier {
    CREATABLE(plMultiModifier, kMultiModifier, plModifier)

protected:
    hsBitVector fFlags;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getFlag(size_t flag) const { return fFlags.get(flag); }
    void setFlag(size_t flag, bool value) { fFlags.set(flag, value); }
};


/* Misc empty modifiers that don't make sense to put elsewhere */
DllClass plElevatorModifier : public virtual plSingleModifier {
    CREATABLE(plElevatorModifier, kElevatorModifier, plSingleModifier)
};

#endif
