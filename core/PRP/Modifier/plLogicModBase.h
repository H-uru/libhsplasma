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

class PLASMA_DLL plLogicModBase : public plSingleModifier
{
    CREATABLE(plLogicModBase, kLogicModBase, plSingleModifier)

public:
    enum Flags
    {
        kLocalElement, kReset, kTriggered, kOneShot, kRequestingTrigger,
        kTypeActivator, kMultiTrigger
    };

protected:
    std::vector<plMessage*> fCommandList;
    hsBitVector fLogicFlags;
    plNotifyMsg* fNotify;
    bool fDisabled;

public:
    plLogicModBase();
    ~plLogicModBase();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plMessage*>& getCommands() const { return fCommandList; }
    std::vector<plMessage*>& getCommands() { return fCommandList; }
    void addCommand(plMessage* cmd) { fCommandList.push_back(cmd); }
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
