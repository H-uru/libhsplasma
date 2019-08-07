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

#include "plDynaDecalMgr.h"

/* plDynaDecalMgr */
void plDynaDecalMgr::read(hsStream* S, plResManager* mgr)
{
    plSynchedObject::read(S, mgr);

    fMatPreShade = mgr->readKey(S);
    fMatRTShade = mgr->readKey(S);

    fTargets.resize(S->readInt());
    for (size_t i=0; i<fTargets.size(); i++)
        fTargets[i] = mgr->readKey(S);
    fPartyObjects.resize(S->readInt());
    for (size_t i=0; i<fPartyObjects.size(); i++)
        fPartyObjects[i] = mgr->readKey(S);

    fMaxNumVerts = S->readInt();
    fMaxNumIdx = S->readInt();
    fWaitOnEnable = S->readInt();
    fIntensity = S->readFloat();
    fWetLength = S->readFloat();
    fRampEnd = S->readFloat();
    fDecayStart = S->readFloat();
    fLifeSpan = S->readFloat();
    fGridSizeU = S->readFloat();
    fGridSizeV = S->readFloat();
    fScale.read(S);
    fPartyTime = S->readFloat();

    fNotifies.resize(S->readInt());
    for (size_t i=0; i<fNotifies.size(); i++)
        fNotifies[i] = mgr->readKey(S);
}

void plDynaDecalMgr::write(hsStream* S, plResManager* mgr)
{
    plSynchedObject::write(S, mgr);

    mgr->writeKey(S, fMatPreShade);
    mgr->writeKey(S, fMatRTShade);

    S->writeInt(fTargets.size());
    for (size_t i=0; i<fTargets.size(); i++)
        mgr->writeKey(S, fTargets[i]);
    S->writeInt(fPartyObjects.size());
    for (size_t i=0; i<fPartyObjects.size(); i++)
        mgr->writeKey(S, fPartyObjects[i]);

    S->writeInt(fMaxNumVerts);
    S->writeInt(fMaxNumIdx);
    S->writeInt(fWaitOnEnable);
    S->writeFloat(fIntensity);
    S->writeFloat(fWetLength);
    S->writeFloat(fRampEnd);
    S->writeFloat(fDecayStart);
    S->writeFloat(fLifeSpan);
    S->writeFloat(fGridSizeU);
    S->writeFloat(fGridSizeV);
    fScale.write(S);
    S->writeFloat(fPartyTime);

    S->writeInt(fNotifies.size());
    for (size_t i=0; i<fNotifies.size(); i++)
        mgr->writeKey(S, fNotifies[i]);
}

void plDynaDecalMgr::IPrcWrite(pfPrcHelper* prc)
{
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("PreShade");
    plResManager::PrcWriteKey(prc, fMatPreShade);
    prc->closeTag();
    prc->writeSimpleTag("RTShade");
    plResManager::PrcWriteKey(prc, fMatRTShade);
    prc->closeTag();

    prc->writeSimpleTag("Targets");
    for (size_t i=0; i<fTargets.size(); i++)
        plResManager::PrcWriteKey(prc, fTargets[i]);
    prc->closeTag();

    prc->writeSimpleTag("PartyObjects");
    for (size_t i=0; i<fPartyObjects.size(); i++)
        plResManager::PrcWriteKey(prc, fPartyObjects[i]);
    prc->closeTag();

    prc->startTag("DynaDecalParams");
    prc->writeParam("MaxNumVerts", fMaxNumVerts);
    prc->writeParam("MaxNumIndices", fMaxNumIdx);
    prc->writeParam("WaitOnEnable", fWaitOnEnable);
    prc->writeParam("PartyTime", fPartyTime);
    prc->endTag(true);

    prc->startTag("DynaDecalMetrics");
    prc->writeParam("Intensity", fIntensity);
    prc->writeParam("WetLength", fWetLength);
    prc->writeParam("RampEnd", fRampEnd);
    prc->writeParam("DecayStart", fDecayStart);
    prc->writeParam("LifeSpan", fLifeSpan);
    prc->endTag();
      prc->startTag("GridSize");
      prc->writeParam("U", fGridSizeU);
      prc->writeParam("V", fGridSizeV);
      prc->endTag(true);
      prc->writeSimpleTag("Scale");
      fScale.prcWrite(prc);
      prc->closeTag();
    prc->closeTag();

    prc->writeSimpleTag("Notifies");
    for (size_t i=0; i<fNotifies.size(); i++)
        plResManager::PrcWriteKey(prc, fNotifies[i]);
    prc->closeTag();
}

void plDynaDecalMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "PreShade") {
        if (tag->hasChildren())
            fMatPreShade = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "RTShade") {
        if (tag->hasChildren())
            fMatRTShade = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Targets") {
        fTargets.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fTargets.size(); i++) {
            fTargets[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "PartyObjects") {
        fPartyObjects.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fPartyObjects.size(); i++) {
            fPartyObjects[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "DynaDecalParams") {
        fMaxNumVerts = tag->getParam("MaxNumVerts", "0").to_uint();
        fMaxNumIdx = tag->getParam("MaxNumIndices", "0").to_uint();
        fWaitOnEnable = tag->getParam("WaintOnEnable", "0").to_uint();
        fPartyTime = tag->getParam("PartyTime", "0").to_float();
    } else if (tag->getName() == "DynaDecalMetrics") {
        fIntensity = tag->getParam("Intensity", "0").to_float();
        fWetLength = tag->getParam("WetLength", "0").to_float();
        fRampEnd = tag->getParam("RampEnd", "0").to_float();
        fDecayStart = tag->getParam("DecayStart", "0").to_float();
        fLifeSpan = tag->getParam("LifeSpan", "0").to_float();

        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() == "GridSize") {
                fGridSizeU = child->getParam("U", "0").to_float();
                fGridSizeV = child->getParam("V", "0").to_float();
            } else if (child->getName() == "Scale") {
                if (child->hasChildren())
                    fScale.prcParse(child->getFirstChild());
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Notifies") {
        fNotifies.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fNotifies.size(); i++) {
            fNotifies[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}
