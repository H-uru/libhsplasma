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

class PLASMA_DLL plLinkEffectsTriggerMsg : public plMessage {
    CREATABLE(plLinkEffectsTriggerMsg, kLinkEffectsTriggerMsg, plMessage)

private:
    unsigned int fInvisLevel, fEffects;
    bool fLeavingAge;
    plKey fLinkKey, fLinkInAnimKey;

public:
    plLinkEffectsTriggerMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getInvisLevel() const { return fInvisLevel; }
    unsigned int getEffects() const { return fEffects; }
    bool isLeavingAge() const { return fLeavingAge; }
    plKey getLinkKey() const { return fLinkKey; }
    plKey getLinkInAnimKey() const { return fLinkInAnimKey; }

    void setInvisLevel(unsigned int level) { fInvisLevel = level; }
    void setEffects(unsigned int effects) { fEffects = effects; }
    void setLeavingAge(bool leaving) { fLeavingAge = leaving; }
    void setLinkKey(plKey linkKey) { fLinkKey = linkKey; }
    void setLinkInAnimKey(plKey animKey) { fLinkInAnimKey = animKey; }
};

#endif
