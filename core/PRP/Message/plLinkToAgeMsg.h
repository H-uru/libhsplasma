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

#ifndef _PLLINKTOAGEMSG_H
#define _PLLINKTOAGEMSG_H

#include "plMessage.h"
#include "PRP/Misc/plAgeLinkInfo.h"

DllClass plLinkToAgeMsg : public plMessage {
    CREATABLE(plLinkToAgeMsg, kLinkToAgeMsg, plMessage)

protected:
    plAgeLinkStruct fAgeLink;
    plAgeLinkEffects fLinkEffects;
    hsByte fStreamVersion, fEoaUnknown;

public:
    plLinkToAgeMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plLinkInDoneMsg : public plMessage {
    CREATABLE(plLinkInDoneMsg, kLinkInDoneMsg, plMessage)
};

#endif
