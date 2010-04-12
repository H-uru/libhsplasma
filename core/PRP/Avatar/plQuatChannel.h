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

#ifndef _PLQUATCHANNEL_H
#define _PLQUATCHANNEL_H

#include "plAGApplicator.h"
#include "PRP/Animation/plController.h"

/* Quat Channels */
DllClass plQuatChannel : public plAGChannel {
    CREATABLE(plQuatChannel, kQuatChannel, plAGChannel)

protected:
    hsQuat fResult;

public:
    hsQuat getResult() const { return fResult; }
    void setResult(const hsQuat& result) { fResult = result; }
};


DllClass plQuatBlend : public plQuatChannel {
    CREATABLE(plQuatBlend, kQuatBlend, plQuatChannel)
};


DllClass plQuatConstant : public plQuatChannel {
    CREATABLE(plQuatConstant, kQuatConstant, plQuatChannel)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plQuatTimeScale : public plQuatChannel {
    CREATABLE(plQuatTimeScale, kQuatTimeScale, plQuatChannel)
};


/* Quat Channel Applicators */
DllClass plQuatChannelApplicator : public plAGApplicator {
    CREATABLE(plQuatChannelApplicator, kQuatChannelApplicator, plAGApplicator)
};

#endif
