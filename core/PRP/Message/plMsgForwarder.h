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

#ifndef _PLMSGFORWARDER_H
#define _PLMSGFORWARDER_H

#include "PRP/KeyedObject/hsKeyedObject.h"

class PLASMA_DLL plMsgForwarder : public hsKeyedObject
{
    CREATABLE(plMsgForwarder, kMsgForwarder, hsKeyedObject)

protected:
    std::vector<plKey> fForwardKeys;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getForwardKeys() const { return fForwardKeys; }
    std::vector<plKey>& getForwardKeys() { return fForwardKeys; }
    void addForwardKey(plKey fwd) { fForwardKeys.emplace_back(std::move(fwd)); }
    void delForwardKey(size_t idx) { fForwardKeys.erase(fForwardKeys.begin() + idx); }
    void clearForwardKeys() { fForwardKeys.clear(); }
};

#endif
