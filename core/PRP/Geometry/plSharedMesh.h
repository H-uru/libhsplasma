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

#ifndef PLSHAREDMESH_H
#define PLSHAREDMESH_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Object/plSceneObject.h"
#include "plGeometrySpan.h"

class PLASMA_DLL plSharedMesh : public virtual hsKeyedObject {
    CREATABLE(plSharedMesh, kSharedMesh, hsKeyedObject)

public:
    enum {
        kDontSaveMorphState = 0x1,
        kLayer0GlobalToMod = 0x2
    };

public:
    std::vector<plGeometrySpan*> fSpans;
    plKey fMorphSet;
    uint8_t fFlags;

public:
    plSharedMesh() : fMorphSet(NULL), fFlags(kDontSaveMorphState) { }
    virtual ~plSharedMesh();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getMorphSet() const { return fMorphSet; }
    uint8_t getFlags() const { return fFlags; }

    void setMorphSet(plKey set) { fMorphSet = set; }
    void setFlags(uint8_t flags) { fFlags = flags; }

    const std::vector<plGeometrySpan*>& getSpans() const { return fSpans; }
    std::vector<plGeometrySpan*>& getSpans() { return fSpans; }
    void addSpan(plGeometrySpan* span) { fSpans.push_back(span); }
    void delSpan(size_t idx);
    void clearSpans();
};

#endif
