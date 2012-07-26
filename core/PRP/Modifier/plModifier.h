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

class PLASMA_DLL plModifier : public virtual plSynchedObject {
    CREATABLE(plModifier, kModifier, plSynchedObject)

public:
    /** Get number of targets (scene objects) referenced by this modifier */
    virtual size_t getTargetsCount() const { return 0; }

    /** Get key of n-th referenced target */
    virtual plKey getTarget(size_t /*pos*/) const { return plKey(); }

    /** Add referenced scene object */
    virtual void addTarget(plKey /*target*/) {}

    /** Remove scene object from target list */
    virtual void removeTarget(plKey /*target*/) {}
};


class PLASMA_DLL plSingleModifier : public virtual plModifier {
    CREATABLE(plSingleModifier, kSingleModifier, plModifier)

protected:
    hsBitVector fFlags;
    plKey fTarget;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getFlag(size_t flag) const { return fFlags.get(flag); }
    void setFlag(size_t flag, bool value) { fFlags.set(flag, value); }

    virtual size_t getTargetsCount() const { return fTarget.Exists()?1:0; }
    virtual plKey getTarget(size_t /*pos*/) const { return fTarget; }
    virtual void addTarget(plKey target) { fTarget = target; };
    virtual void removeTarget(plKey /*target*/) { fTarget = plKey(); }
};


class PLASMA_DLL plMultiModifier : public virtual plModifier {
    CREATABLE(plMultiModifier, kMultiModifier, plModifier)

protected:
    hsBitVector fFlags;
    std::vector<plKey> fTargets;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getFlag(size_t flag) const { return fFlags.get(flag); }
    void setFlag(size_t flag, bool value) { fFlags.set(flag, value); }

    virtual size_t getTargetsCount() const { return fTargets.size(); }
    virtual plKey getTarget(size_t pos) const { return fTargets.at(pos); };
    virtual void addTarget(plKey target) { fTargets.push_back(target); };
    virtual void removeTarget(plKey target);
};


/* Misc empty modifiers that don't make sense to put elsewhere */
class PLASMA_DLL plElevatorModifier : public virtual plSingleModifier {
    CREATABLE(plElevatorModifier, kElevatorModifier, plSingleModifier)
};

#endif
