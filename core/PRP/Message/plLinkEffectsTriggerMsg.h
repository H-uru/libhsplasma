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

#ifndef _PLLINKEFFECTSTRIGGERMSG_H
#define _PLLINKEFFECTSTRIGGERMSG_H

#include "plMessage.h"

class PLASMA_DLL plLinkEffectsTriggerMsg : public plMessage
{
    CREATABLE(plLinkEffectsTriggerMsg, kLinkEffectsTriggerMsg, plMessage)

private:
    unsigned int fInvisLevel, fEffects;
    bool fLeavingAge;
    plKey fLinkKey, fLinkInAnimKey;

public:
    plLinkEffectsTriggerMsg() : fInvisLevel(), fEffects(), fLeavingAge() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned int getInvisLevel() const { return fInvisLevel; }
    unsigned int getEffects() const { return fEffects; }
    bool isLeavingAge() const { return fLeavingAge; }
    plKey getLinkKey() const { return fLinkKey; }
    plKey getLinkInAnimKey() const { return fLinkInAnimKey; }

    void setInvisLevel(unsigned int level) { fInvisLevel = level; }
    void setEffects(unsigned int effects) { fEffects = effects; }
    void setLeavingAge(bool leaving) { fLeavingAge = leaving; }
    void setLinkKey(plKey linkKey) { fLinkKey = std::move(linkKey); }
    void setLinkInAnimKey(plKey animKey) { fLinkInAnimKey = std::move(animKey); }
};

#endif
