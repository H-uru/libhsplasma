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

#ifndef _PLDETECTORMODIFIER_H
#define _PLDETECTORMODIFIER_H

#include "PRP/Modifier/plModifier.h"

class PLASMA_DLL plDetectorModifier : public plSingleModifier
{
    CREATABLE(plDetectorModifier, kDetectorModifier, plSingleModifier)

protected:
    std::vector<plKey> fReceivers;
    plKey fRemoteMod, fProxyKey;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getReceivers() const { return fReceivers; }
    std::vector<plKey>& getReceivers() { return fReceivers; }
    void addReceiver(plKey rcvr) { fReceivers.emplace_back(std::move(rcvr)); }
    void delReceiver(size_t idx) { fReceivers.erase(fReceivers.begin() + idx); }
    void clearReceivers() { fReceivers.clear(); }

    plKey getRemoteMod() const { return fRemoteMod; }
    plKey getProxy() const { return fProxyKey; }

    void setRemoteMod(plKey mod) { fRemoteMod = std::move(mod); }
    void setProxy(plKey proxy) { fProxyKey = std::move(proxy); }
};


class PLASMA_DLL plPickingDetector : public plDetectorModifier
{
    CREATABLE(plPickingDetector, kPickingDetector, plDetectorModifier)
};

#endif
