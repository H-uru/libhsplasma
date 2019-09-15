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

#ifndef _PLACTIVATORCONDITIONALOBJECT_H
#define _PLACTIVATORCONDITIONALOBJECT_H

#include "plConditionalObject.h"

class PLASMA_DLL plActivatorConditionalObject : public plConditionalObject
{
    CREATABLE(plActivatorConditionalObject, kActivatorConditionalObject,
              plConditionalObject)

protected:
    std::vector<plKey> fActivators;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getActivators() const { return fActivators; }
    std::vector<plKey>& getActivators() { return fActivators; }
    void addActivator(plKey activator) { fActivators.emplace_back(std::move(activator)); }
    void delActivator(size_t idx) { fActivators.erase(fActivators.begin() + idx); }
    void clearActivators() { fActivators.clear(); }
};


class PLASMA_DLL plActivatorActivatorConditionalObject : public plActivatorConditionalObject
{
    CREATABLE(plActivatorActivatorConditionalObject,
              kActivatorActivatorConditionalObject,
              plActivatorConditionalObject)
};


class PLASMA_DLL plVolActivatorConditionalObject : public plActivatorConditionalObject
{
    CREATABLE(plVolActivatorConditionalObject,
              kVolActivatorConditionalObject,
              plActivatorConditionalObject)
};

#endif
