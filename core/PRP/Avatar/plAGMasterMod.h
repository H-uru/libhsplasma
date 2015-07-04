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

#ifndef _PLAGMASTERMOD_H
#define _PLAGMASTERMOD_H

#include "PRP/Modifier/plModifier.h"

class PLASMA_DLL plAGMasterMod : public virtual plModifier {
    CREATABLE(plAGMasterMod, kAGMasterMod, plModifier)

protected:
    std::vector<plKey> fPrivateAnims, fEoaKeys2;
    plString fGroupName; // Only used in UU, auto-deleted in PotS and newer
    bool fIsGrouped, fIsGroupMaster;
    plKey fMsgForwarder;

public:
    plAGMasterMod() : fIsGrouped(false), fIsGroupMaster(false) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const std::vector<plKey>& getPrivateAnims() const { return fPrivateAnims; }
    std::vector<plKey>& getPrivateAnims() { return fPrivateAnims; }
    void addPrivateAnim(plKey key) { fPrivateAnims.push_back(key); }
    void delPrivateAnim(size_t idx) { fPrivateAnims.erase(fPrivateAnims.begin() + idx); }
    void clearPrivateAnims() { fPrivateAnims.clear(); }

    const std::vector<plKey>& getEoaKeys() const { return fEoaKeys2; }
    std::vector<plKey>& getEoaKeys() { return fEoaKeys2; }
    void addEoaKey(plKey key) { fEoaKeys2.push_back(key); }
    void delEoaKey(size_t idx) { fEoaKeys2.erase(fEoaKeys2.begin() + idx); }
    void clearEoaKeys() { fEoaKeys2.clear(); }

    plString getGroupName() const { return fGroupName; }
    bool getIsGrouped() const { return fIsGrouped; }
    bool getIsGroupMaster() const { return fIsGroupMaster; }
    plKey getMsgForwarder() const { return fMsgForwarder; }

    void setGroupName(const plString& value) { fGroupName = value; }
    void setIsGrouped(bool value) { fIsGrouped = value; }
    void setIsGroupMaster(bool value) { fIsGroupMaster = value; }
    void setMsgForwarder(plKey value) { fMsgForwarder = value; }
};

#endif
