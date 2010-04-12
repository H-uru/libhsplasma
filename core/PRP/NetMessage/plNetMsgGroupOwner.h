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

#ifndef _PLNETMSGGROUPOWNER_H
#define _PLNETMSGGROUPOWNER_H

#include "plNetMessage.h"
#include "plNetGroupId.h"

DllClass plNetMsgGroupOwner : public plNetMsgServerToClient {
    CREATABLE(plNetMsgGroupOwner, kNetMsgGroupOwner, plNetMsgServerToClient)

public:
    DllStruct GroupInfo {
        plNetGroupId fGroupID;
        bool fOwnIt;

        GroupInfo();
    };

private:
    hsTArray<GroupInfo> fGroups;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<GroupInfo>& getGroups() const { return fGroups; }
    hsTArray<GroupInfo>& getGroups() { return fGroups; }
    void addGroup(const GroupInfo& grp) { fGroups.append(grp); }
    void delGroup(size_t idx) { fGroups.remove(idx); }
    void clearGroups() { fGroups.clear(); }
};

#endif
