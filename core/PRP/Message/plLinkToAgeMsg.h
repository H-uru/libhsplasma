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
#include "PRP/plCreatableListHelper.h"

class PLASMA_DLL plLinkToAgeMsg : public plMessage
{
    CREATABLE(plLinkToAgeMsg, kLinkToAgeMsg, plMessage)

protected:
    plAgeLinkStruct fAgeLink;
    plAgeLinkEffects fLinkEffects;
    uint8_t fStreamVersion, fEoaUnknown;

public:
    plLinkToAgeMsg() : fStreamVersion(), fEoaUnknown() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const plAgeLinkStruct& getAgeLink() const { return fAgeLink; }
    plAgeLinkStruct& getAgeLink() { return fAgeLink; }

    const plAgeLinkEffects& getLinkEffects() const { return fLinkEffects; }
    plAgeLinkEffects& getLinkEffects() { return fLinkEffects; }

    uint8_t getStreamVersion() const { return fStreamVersion; }
    uint8_t getEoaUnknown() const { return fEoaUnknown; }

    void setStreamVersion(uint8_t ver) { fStreamVersion = ver; }
    void setEoaUnknown(uint8_t value) { fEoaUnknown = value; }
};


class PLASMA_DLL plLinkInDoneMsg : public plMessage
{
    CREATABLE(plLinkInDoneMsg, kLinkInDoneMsg, plMessage)
};


class PLASMA_DLL plLinkingMgrMsg : public plMessage
{
    CREATABLE(plLinkingMgrMsg, kLinkingMgrMsg, plMessage)

protected:
    uint8_t fLinkingMgrCmd;
    plCreatableListHelper fCreatables;

public:
    plLinkingMgrMsg() : fLinkingMgrCmd() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;
};

#endif
