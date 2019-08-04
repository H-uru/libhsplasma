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

#include "plWaveSet.h"

/* plWaveSet6 */
void plWaveSet6::read(hsStream* S, plResManager* mgr)
{
    plMultiModifier::read(S, mgr);
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void plWaveSet6::write(hsStream* S, plResManager* mgr)
{
    plMultiModifier::write(S, mgr);
    throw hsNotImplementedException(__FILE__, __LINE__);
}

void plWaveSet6::IPrcWrite(pfPrcHelper* prc)
{
    plMultiModifier::IPrcWrite(prc);
    prc->writeComment("plWaveSet6 Not Implemented");
}

void plWaveSet6::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    throw hsNotImplementedException(__FILE__, __LINE__);
}


/* plWaveSet7 */
void plWaveSet7::read(hsStream* S, plResManager* mgr)
{
    plMultiModifier::read(S, mgr);

    fMaxLen = S->readFloat();
    fState.read(S);

    fShores.resize(S->readInt());
    for (size_t i=0; i<fShores.size(); i++)
        fShores[i] = mgr->readKey(S);
    fDecals.resize(S->readInt());
    for (size_t i=0; i<fDecals.size(); i++)
        fDecals[i] = mgr->readKey(S);
    fEnvMap = mgr->readKey(S);
    if (fFlags[kHasRefObject])
        fRefObj = mgr->readKey(S);
}

void plWaveSet7::write(hsStream* S, plResManager* mgr)
{
    plMultiModifier::write(S, mgr);

    S->writeFloat(fMaxLen);
    fState.write(S);

    S->writeInt(fShores.size());
    for (size_t i=0; i<fShores.size(); i++)
        mgr->writeKey(S, fShores[i]);
    S->writeInt(fDecals.size());
    for (size_t i=0; i<fDecals.size(); i++)
        mgr->writeKey(S, fDecals[i]);
    mgr->writeKey(S, fEnvMap);
    if (fFlags[kHasRefObject])
        mgr->writeKey(S, fRefObj);
}

void plWaveSet7::IPrcWrite(pfPrcHelper* prc)
{
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("WaveSet7Params");
    prc->writeParam("MaxLen", fMaxLen);
    prc->endTag(true);

    fState.prcWrite(prc);

    prc->writeSimpleTag("Shores");
    for (size_t i=0; i<fShores.size(); i++)
        plResManager::PrcWriteKey(prc, fShores[i]);
    prc->closeTag();
    prc->writeSimpleTag("Decals");
    for (size_t i=0; i<fDecals.size(); i++)
        plResManager::PrcWriteKey(prc, fDecals[i]);
    prc->closeTag();

    prc->writeSimpleTag("EnvMap");
    plResManager::PrcWriteKey(prc, fEnvMap);
    prc->closeTag();

    if (fFlags[kHasRefObject]) {
        prc->writeSimpleTag("RefObject");
        plResManager::PrcWriteKey(prc, fRefObj);
        prc->closeTag();
    }
}

void plWaveSet7::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "WaveSet7Params") {
        fMaxLen = tag->getParam("MaxLen", "0").to_float();
    } else if (tag->getName() == "plFixedWaterState7") {
        fState.prcParse(tag);
    } else if (tag->getName() == "Shores") {
        fShores.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fShores.size(); i++) {
            fShores[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Decals") {
        fDecals.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fDecals.size(); i++) {
            fDecals[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "EnvMap") {
        if (tag->hasChildren())
            fEnvMap = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "RefObject") {
        if (tag->hasChildren())
            fRefObj = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
