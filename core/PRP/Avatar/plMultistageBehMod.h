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

class PLASMA_DLL plMultistageBehMod : public plSingleModifier
{
    CREATABLE(plMultistageBehMod, kMultistageBehMod, plSingleModifier)

protected:
    std::vector<plAnimStage*> fStages;
    bool fFreezePhys, fSmartSeek, fReverseFBControlsOnRelease;
    std::vector<plKey> fReceivers;

public:
    plMultistageBehMod()
        : fFreezePhys(), fSmartSeek(), fReverseFBControlsOnRelease() { }
    ~plMultistageBehMod();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plAnimStage*>& getStages() const { return fStages; }
    std::vector<plAnimStage*>& getStages() { return fStages; }
    void addStage(plAnimStage* stage) { fStages.push_back(stage); }
    void delStage(size_t idx);
    void clearStages();

    const std::vector<plKey>& getReceivers() const { return fReceivers; }
    std::vector<plKey>& getReceivers() { return fReceivers; }
    void addReceiver(plKey receiver) { fReceivers.emplace_back(std::move(receiver)); }
    void delReceiver(size_t idx) { fReceivers.erase(fReceivers.begin() + idx); }
    void clearReceivers() { fReceivers.clear(); }

    bool getFreezePhys() const { return fFreezePhys; }
    bool getSmartSeek() const { return fSmartSeek; }
    bool getReverseFBControlsOnRelease() const { return fReverseFBControlsOnRelease; }

    void setFreezePhys(bool freeze) { fFreezePhys = freeze; }
    void setSmartSeek(bool seek) { fSmartSeek = seek; }
    void setReverseFBControlsOnRelease(bool reverse) { fReverseFBControlsOnRelease = reverse; }
};

#endif
