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

#ifndef _PLVAULTNODEREF_H
#define _PLVAULTNODEREF_H

#include "../Sys/plUnifiedTime.h"

class PLASMA_DLL plVaultNodeRef
{
protected:
    unsigned int fSaver, fParent, fChild;
    plUnifiedTime fAutoTime;
    bool fSeen;

public:
    plVaultNodeRef() : fSaver(), fParent(), fChild(), fSeen() { }

    void read(hsStream* S);
    void write(hsStream* S);

public:
    unsigned int getSaver() const { return fSaver; }
    unsigned int getParent() const { return fParent; }
    unsigned int getChild() const { return fChild; }
    plUnifiedTime getAutoTime() const { return fAutoTime; }
    bool getSeen() const { return fSeen; }

    void setSaver(unsigned int id) { fSaver = id; }
    void setParent(unsigned int id) { fParent = id; }
    void setChild(unsigned int id) { fChild = id; }
    void setAutoTime(const plUnifiedTime& time) { fAutoTime = time; }
    void setSeen(bool seen) { fSeen = seen; }
};

#endif
