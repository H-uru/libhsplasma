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

#ifndef _PLSITTINGMODIFIER_H
#define _PLSITTINGMODIFIER_H

#include "PRP/Modifier/plModifier.h"

class PLASMA_DLL plSittingModifier : public plSingleModifier
{
    CREATABLE(plSittingModifier, kSittingModifier, plSingleModifier)

public:
    enum
    {
        kApproachFront = 0x1,
        kApproachLeft = 0x2,
        kApproachRight = 0x4,
        kApproachRear = 0x8,
        kApproachMask = kApproachFront | kApproachLeft |
                        kApproachRight | kApproachRear,
        kDisableForward = 0x10
    };

protected:
    uint8_t fMiscFlags;
    std::vector<plKey> fNotifyKeys;
    plKey fTriggeredAvatarKey;

public:
    plSittingModifier() : fMiscFlags() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    uint8_t getMiscFlags() const { return fMiscFlags; }
    void setMiscFlags(uint8_t value) { fMiscFlags = value; }

    const std::vector<plKey>& getNotifyKeys() const { return fNotifyKeys; }
    std::vector<plKey>& getNotifyKeys() { return fNotifyKeys; }
    void addNotifyKey(plKey notify) { fNotifyKeys.emplace_back(std::move(notify)); }
    void delNotifyKey(size_t idx) { fNotifyKeys.erase(fNotifyKeys.begin() + idx); }
    void clearNotifyKeys() { fNotifyKeys.clear(); }
};

#endif
