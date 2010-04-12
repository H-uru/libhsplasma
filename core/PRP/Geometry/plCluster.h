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
#include "Util/hsTArray.hpp"

DllClass plCluster {
protected:
    hsTArray<plSpanInstance*> fInstances;
    plSpanEncoding fEncoding;
    class plClusterGroup* fGroup;   // Not owned by the cluster

public:
    plCluster() { }
    ~plCluster();

    void read(hsStream* S, class plClusterGroup* group);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag, class plClusterGroup* group);

    const plSpanEncoding& getEncoding() const { return fEncoding; }
    plSpanEncoding& getEncoding() { return fEncoding; }

    plClusterGroup* getGroup() const { return fGroup; }
    void setGroup(plClusterGroup* group) { fGroup = group; }

    const hsTArray<plSpanInstance*>& getInstances() const { return fInstances; }
    hsTArray<plSpanInstance*>& getInstances() { return fInstances; }
    void addInstance(plSpanInstance* inst) { fInstances.append(inst); }
    void delInstance(size_t idx);
    void clearInstances();
};

#endif
