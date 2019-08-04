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

#include "plSimulationInterface.h"

plSimulationInterface::plSimulationInterface() : fUruInt()
{
    fProps.setName(kDisable, "kDisable");
    fProps.setName(kWeightless, "kWeightless");
    fProps.setName(kPinned, "kPinned");
    fProps.setName(kWarp, "kWarp");
    fProps.setName(kUpright, "kUpright");
    fProps.setName(kPassive, "kPassive");
    fProps.setName(kRotationForces, "kRotationForces");
    fProps.setName(kCameraAvoidObject, "kCameraAvoidObject");
    fProps.setName(kPhysAnim, "kPhysAnim");
    fProps.setName(kStartInactive, "kStartInactive");
    fProps.setName(kNoSynchronize, "kNoSynchronize");
    fProps.setName(kSuppressed, "kSuppressed");
    fProps.setName(kNoOwnershipChange, "kNoOwnershipChange");
    fProps.setName(kAvAnimPushable, "kAvAnimPushable");
}

void plSimulationInterface::read(hsStream* S, plResManager* mgr)
{
    plObjInterface::read(S, mgr);

    if (S->getVer().isUru()) {
        // Yes, really :(
        fProps.read(S);
        fUruInt = S->readInt(); // 0 for POTS, 0xFFFFFFFF for some marker simulation interfaces in UU
    }
    fPhysical = mgr->readKey(S);
}

void plSimulationInterface::write(hsStream* S, plResManager* mgr)
{
    plObjInterface::write(S, mgr);

    if (S->getVer().isUru()) {
        fProps.write(S);
        S->writeInt(fUruInt);
    }
    mgr->writeKey(S, fPhysical);
}

void plSimulationInterface::IPrcWrite(pfPrcHelper* prc)
{
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Physical");
    plResManager::PrcWriteKey(prc, fPhysical);
    prc->closeTag();
}

void plSimulationInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Physical") {
        if (tag->hasChildren())
            fPhysical = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
