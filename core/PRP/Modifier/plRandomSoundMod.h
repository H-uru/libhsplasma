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

#ifndef _PLRANDOMSOUNDMOD_H
#define _PLRANDOMSOUNDMOD_H

#include "plRandomCommandMod.h"

class HSPLASMA_EXPORT plRandomSoundModGroup
{
protected:
    std::vector<unsigned short> fIndices;
    short fGroupedIdx;

public:
    plRandomSoundModGroup() : fGroupedIdx() { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    const std::vector<unsigned short>& getIndices() const { return fIndices; }
    std::vector<unsigned short>& getIndices() { return fIndices; }
    void addIndex(unsigned short index) { fIndices.push_back(index); }
    void delIndex(size_t idx) { fIndices.erase(fIndices.begin() + idx); }
    void clearIndices() { fIndices.clear(); }

    short getGroupedIdx() const { return fGroupedIdx; }
    void setGroupedIdx(short groupedIdx) { fGroupedIdx = groupedIdx; }
};


class HSPLASMA_EXPORT plRandomSoundMod : public plRandomCommandMod
{
    CREATABLE(plRandomSoundMod, kRandomSoundMod, plRandomCommandMod)

protected:
    std::vector<plRandomSoundModGroup> fGroups;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plRandomSoundModGroup>& getGroups() const { return fGroups; }
    std::vector<plRandomSoundModGroup>& getGroups() { return fGroups; }
    void addGroup(plRandomSoundModGroup group) { fGroups.emplace_back(std::move(group)); }
    void delGroup(size_t idx) { fGroups.erase(fGroups.begin() + idx); }
    void clearGroups() { fGroups.clear(); }
};

#endif
