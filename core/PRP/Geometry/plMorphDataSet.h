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

#ifndef _PLMORPHDATASET_H
#define _PLMORPHDATASET_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "plMorphArray.h"

class HSPLASMA_EXPORT plMorphDataSet : public hsKeyedObject
{
    CREATABLE(plMorphDataSet, kMorphDataSet, hsKeyedObject)

protected:
    std::vector<plMorphArray> fMorphs;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plMorphArray>& getMorphs() const { return fMorphs; }
    std::vector<plMorphArray>& getMorphs() { return fMorphs; }
};

#endif
