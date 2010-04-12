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

#ifndef _PLNETMSGPLAYERPAGE_H
#define _PLNETMSGPLAYERPAGE_H

#include "plNetMessage.h"
#include "PRP/KeyedObject/plUoid.h"

DllClass plNetMsgPlayerPage : public plNetMessage {
    CREATABLE(plNetMsgPlayerPage, kNetMsgPlayerPage, plNetMessage)

private:
    unsigned char fUnload;
    plUoid fUoid;

public:
    plNetMsgPlayerPage();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

private:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned char getUnload() const { return fUnload; }
    plUoid getUoid() const { return fUoid; }

    void setUnload(unsigned char unload) { fUnload = unload; }
    void setUoid(const plUoid& uoid) { fUoid = uoid; }
};

#endif
