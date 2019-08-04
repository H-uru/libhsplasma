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

#ifndef _PLRELEVANCEREGION_H
#define _PLRELEVANCEREGION_H

#include "PRP/Object/plObjInterface.h"
#include "Util/hsBitVector.h"

class PLASMA_DLL plRelevanceRegion : public plObjInterface
{
    CREATABLE(plRelevanceRegion, kRelevanceRegion, plObjInterface)

protected:
    plKey fRegion;
    hsBitVector fRegionsICareAbout;
    unsigned int fMgrIdx;

public:
    plRelevanceRegion() : fMgrIdx((unsigned int)-1) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
