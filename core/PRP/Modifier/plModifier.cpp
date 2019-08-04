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

#include "plModifier.h"
#include <algorithm>

/* plSingleModifier */
void plSingleModifier::read(hsStream* S, plResManager* mgr)
{
    plSynchedObject::read(S, mgr);
    fFlags.read(S);
}

void plSingleModifier::write(hsStream* S, plResManager* mgr)
{
    plSynchedObject::write(S, mgr);
    fFlags.write(S);
}

void plSingleModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("ModFlags");
    fFlags.prcWrite(prc);
    prc->closeTag();
}

void plSingleModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ModFlags") {
        if (tag->hasChildren())
            fFlags.prcParse(tag->getFirstChild());
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}


/* plMultiModifier */
void plMultiModifier::read(hsStream* S, plResManager* mgr)
{
    plSynchedObject::read(S, mgr);
    fFlags.read(S);
}

void plMultiModifier::write(hsStream* S, plResManager* mgr)
{
    plSynchedObject::write(S, mgr);
    fFlags.write(S);
}

void plMultiModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("ModFlags");
    fFlags.prcWrite(prc);
    prc->closeTag();
}

void plMultiModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ModFlags") {
        if (tag->hasChildren())
            fFlags.prcParse(tag->getFirstChild());
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}

void plMultiModifier::removeTarget(const plKey& target)
{
    auto it = std::find(fTargets.begin(), fTargets.end(), target);

    if (it == fTargets.end())
        throw hsBadParamException(__FILE__, __LINE__, "Trying to remove invalid target");

    fTargets.erase(it);
}
