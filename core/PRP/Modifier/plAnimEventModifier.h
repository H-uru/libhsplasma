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

#ifndef _PLANIMEVENTMODIFIER_H
#define _PLANIMEVENTMODIFIER_H

#include "plModifier.h"
#include "PRP/Message/plMessage.h"

class HSPLASMA_EXPORT plAnimEventModifier : public plSingleModifier
{
    CREATABLE(plAnimEventModifier, kAnimEventModifier, plSingleModifier)

protected:
    std::vector<plKey> fReceivers;
    plMessage* fCallback;
    bool fDisabled;

public:
    plAnimEventModifier() : fCallback(), fDisabled() { }
    ~plAnimEventModifier();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getReceivers() const { return fReceivers; }
    std::vector<plKey>& getReceivers() { return fReceivers; }
    plMessage* getCallback() const { return fCallback; }
    bool isDisabled() const { return fDisabled; }

    void setCallback(plMessage* callback);
    void setDisabled(bool disabled) { fDisabled = disabled; }
};

#endif
