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

#ifndef _PLLOGICMODBASE_H
#define _PLLOGICMODBASE_H

#include "plModifier.h"
#include "PRP/Message/plNotifyMsg.h"

DllClass plLogicModBase : public virtual plSingleModifier {
    CREATABLE(plLogicModBase, kLogicModBase, plSingleModifier)

public:
    enum Flags {
        kLocalElement, kReset, kTriggered, kOneShot, kRequestingTrigger,
        kTypeActivator, kMultiTrigger
    };

protected:
    hsTArray<plMessage*> fCommandList;
    hsBitVector fLogicFlags;
    plNotifyMsg* fNotify;
    bool fDisabled;

public:
    plLogicModBase();
    virtual ~plLogicModBase();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plMessage*> getCommands() const { return fCommandList; }
    hsTArray<plMessage*> getCommands() { return fCommandList; }
    void addCommand(plMessage* cmd) { fCommandList.append(cmd); }
    void delCommand(size_t idx);
    void clearCommands();

    plNotifyMsg* getNotify() const { return fNotify; }
    bool isDisabled() const { return fDisabled; }

    void setNotify(plNotifyMsg* notify);
    void setDisabled(bool disabled) { fDisabled = disabled; }

    bool getLogicFlag(size_t flag) const { return fLogicFlags.get(flag); }
    void setLogicFlag(size_t flag, bool value) { return fLogicFlags.set(flag, value); }
};

#endif
