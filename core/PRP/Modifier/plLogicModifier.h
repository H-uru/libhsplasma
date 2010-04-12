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

#ifndef _PLLOGICMODIFIER_H
#define _PLLOGICMODIFIER_H

#include "plLogicModBase.h"

DllClass plLogicModifier : public plLogicModBase {
    CREATABLE(plLogicModifier, kLogicModifier, plLogicModBase)

protected:
    hsTArray<plKey> fConditionList;
    unsigned int fMyCursor;
    plKey fParent;

public:
    plLogicModifier();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getConditions() const { return fConditionList; }
    hsTArray<plKey>& getConditions() { return fConditionList; }
    void addCondition(plKey cond) { fConditionList.append(cond); }
    void delCondition(size_t idx) { fConditionList.remove(idx); }
    void clearConditions() { fConditionList.clear(); }

    unsigned int getCursor() const { return fMyCursor; }
    plKey getParent() const { return fParent; }

    void setCursor(unsigned int cursor) { fMyCursor = cursor; }
    void setParent(plKey parent) { fParent = parent; }
};

#endif
