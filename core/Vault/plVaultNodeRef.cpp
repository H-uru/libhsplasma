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

#include "plVaultNodeRef.h"

plVaultNodeRef::plVaultNodeRef()
              : fSaver(0), fParent(0), fChild(0), fSeen(false) { }

plVaultNodeRef::plVaultNodeRef(const plVaultNodeRef& init)
              : fSaver(init.fSaver), fParent(init.fParent), fChild(init.fChild),
                fAutoTime(init.fAutoTime), fSeen(init.fSeen) { }

plVaultNodeRef& plVaultNodeRef::operator=(const plVaultNodeRef& init) {
    fSaver = init.fSaver;
    fParent = init.fParent;
    fChild = init.fChild;
    fAutoTime = init.fAutoTime;
    fSeen = init.fSeen;
    return *this;
}

void plVaultNodeRef::read(hsStream* S) {
    fSaver = S->readInt();
    fParent = S->readInt();
    fChild = S->readInt();
    fAutoTime.read(S);
    fSeen = S->readBool();
}

void plVaultNodeRef::write(hsStream* S) {
    S->writeInt(fSaver);
    S->writeInt(fParent);
    S->writeInt(fChild);
    fAutoTime.write(S);
    S->writeBool(fSeen);
}
