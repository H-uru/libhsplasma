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

#ifndef _PLAXISANIMMODIFIER_H
#define _PLAXISANIMMODIFIER_H

#include "plModifier.h"
#include "PRP/Message/plNotifyMsg.h"

class PLASMA_DLL plAxisAnimModifier : public plSingleModifier
{
    CREATABLE(plAxisAnimModifier, kAxisAnimModifier, plSingleModifier)

private:
    plKey fXAnim, fYAnim, fNotificationKey;
    plNotifyMsg* fNotify;
    ST::string fAnimLabel;
    bool fAllOrNothing;

    // Lots of unknown EOA parameters:
    bool b65, b66, b70;
    std::vector<float> af38;
    std::vector<float> af40;
    float f48, f58, f5c;
    float fb0, fac, fa0, f98, fa4;
    bool b60, b90, bb4, bb5;

public:
    plAxisAnimModifier() : fNotify(), fAllOrNothing() { }
    ~plAxisAnimModifier();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getXAnim() const { return fXAnim; }
    plKey getYAnim() const { return fYAnim; }
    plKey getNotificationKey() const { return fNotificationKey; }
    plNotifyMsg* getNotify() const { return fNotify; }
    ST::string getAnimLabel() const { return fAnimLabel; }
    bool getAllOrNothing() const { return fAllOrNothing; }

    void setXAnim(plKey anim) { fXAnim = std::move(anim); }
    void setYAnim(plKey anim) { fYAnim = std::move(anim); }
    void setNotificationKey(plKey notify) { fNotificationKey = std::move(notify); }
    void setAnimLabel(const ST::string& label) { fAnimLabel = label; }
    void setAllOrNothing(bool value) { fAllOrNothing = value; }
    void setNotify(plNotifyMsg* msg);
};

#endif
