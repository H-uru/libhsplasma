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

#ifndef _PLMULTISTAGEBEHMOD_H
#define _PLMULTISTAGEBEHMOD_H

#include "PRP/Modifier/plModifier.h"
#include "plAnimStage.h"

DllClass plMultistageBehMod : public virtual plSingleModifier {
    CREATABLE(plMultistageBehMod, kMultistageBehMod, plSingleModifier)

protected:
    hsTArray<plAnimStage*> fStages;
    bool fFreezePhys, fSmartSeek, fReverseFBControlsOnRelease;
    hsTArray<plKey> fReceivers;

public:
    plMultistageBehMod();
    virtual ~plMultistageBehMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plAnimStage*>& getStages() const { return fStages; }
    hsTArray<plAnimStage*>& getStages() { return fStages; }
    void addStage(plAnimStage* stage) { fStages.append(stage); }
    void delStage(size_t idx);
    void clearStages();

    const hsTArray<plKey>& getReceivers() const { return fReceivers; }
    hsTArray<plKey>& getReceivers() { return fReceivers; }
    void addReceiver(plKey receiver) { fReceivers.append(receiver); }
    void delReceiver(size_t idx) { fReceivers.remove(idx); }
    void clearReceivers() { fReceivers.clear(); }

    bool getFreezePhys() const { return fFreezePhys; }
    bool getSmartSeek() const { return fSmartSeek; }
    bool getReverseFBControlsOnRelease() const { return fReverseFBControlsOnRelease; }

    void setFreezePhys(bool freeze) { fFreezePhys = freeze; }
    void setSmartSeek(bool seek) { fSmartSeek = seek; }
    void setReverseFBControlsOnRelease(bool reverse) { fReverseFBControlsOnRelease = reverse; }
};

#endif
