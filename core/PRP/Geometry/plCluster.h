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

#ifndef _PLCLUSTER_H
#define _PLCLUSTER_H

#include "plSpanInstance.h"

class plClusterGroup;

class PLASMA_DLL plCluster
{
protected:
    std::vector<plSpanInstance*> fInstances;
    plSpanEncoding fEncoding;
    plClusterGroup* fGroup;   // Not owned by the cluster

public:
    plCluster() : fGroup() { }
    ~plCluster();

    void read(hsStream* S, class plClusterGroup* group);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag, class plClusterGroup* group);

    const plSpanEncoding& getEncoding() const { return fEncoding; }
    plSpanEncoding& getEncoding() { return fEncoding; }

    plClusterGroup* getGroup() const { return fGroup; }
    void setGroup(plClusterGroup* group) { fGroup = group; }

    const std::vector<plSpanInstance*>& getInstances() const { return fInstances; }
    std::vector<plSpanInstance*>& getInstances() { return fInstances; }
    void addInstance(plSpanInstance* inst) { fInstances.push_back(inst); }
    void delInstance(size_t idx);
    void clearInstances();
};

#endif
