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

#ifndef _PLNETMSGRELEVANCEREGIONS_H
#define _PLNETMSGRELEVANCEREGIONS_H

#include "plNetMessage.h"
#include "Util/hsBitVector.h"

DllClass plNetMsgRelevanceRegions : public plNetMessage {
    CREATABLE(plNetMsgRelevanceRegions, kNetMsgRelevanceRegions, plNetMessage)

private:
    hsBitVector fRegionsICareAbout;
    hsBitVector fRegionsImIn;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool inRegion(size_t region) { return fRegionsImIn.get(region); }
    bool careAboutRegion(size_t region) { return fRegionsICareAbout.get(region); }
    void setRegion(size_t region, bool in, bool careAbout);
};

#endif
