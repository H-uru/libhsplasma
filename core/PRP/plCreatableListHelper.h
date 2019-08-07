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

#ifndef _PLCREATABLELISTHELPER_H
#define _PLCREATABLELISTHELPER_H

#include "plCreatable.h"
#include "ResManager/plResManager.h"

class PLASMA_DLL plCreatableListHelper : public plCreatable
{
    CREATABLE(plCreatableListHelper, kCreatableListHelper, plCreatable)

public:
    enum Flags
    {
        kWantCompression = (1<<0),
        kCompressed      = (1<<1),
        kWritten         = (1<<2),
    };

protected:
    uint8_t fFlags;
    std::map<uint16_t, plCreatable*> fCreatables;

public:
    plCreatableListHelper() : fFlags(kWantCompression) { }
    ~plCreatableListHelper() { clearCreatables(); }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    uint8_t getFlags() const { return fFlags; }
    void setFlags(uint8_t flags) { fFlags = flags; }

    std::map<uint16_t, plCreatable*>& getCreatables() { return fCreatables; }
    const std::map<uint16_t, plCreatable*>& getCreatables() const { return fCreatables; }
    void clearCreatables();
};

#endif
