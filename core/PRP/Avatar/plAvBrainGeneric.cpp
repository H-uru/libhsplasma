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

#include "plAvBrainGeneric.h"

plAvBrainGeneric::~plAvBrainGeneric()
{
    for (auto stage = fStages.begin(); stage != fStages.end(); ++stage)
        delete *stage;
    delete fStartMessage;
    delete fEndMessage;
}

void plAvBrainGeneric::read(hsStream* S, plResManager* mgr)
{
    plArmatureBrain::read(S, mgr);

    clearStages();
    fStages.resize(S->readInt());
    for (size_t i=0; i<fStages.size(); i++) {
        fStages[i] = mgr->ReadCreatableC<plAnimStage>(S);
        fStages[i]->readAux(S);
    }

    fCurStage = S->readInt();
    fType = (BrainType)S->readInt();
    fExitFlags = S->readInt();
    fMode = (Mode)S->readByte();
    fForward = S->readBool();

    if (S->readBool())
        setStartMessage(mgr->ReadCreatableC<plMessage>(S));
    else
        setStartMessage(nullptr);

    if (S->readBool())
        setEndMessage(mgr->ReadCreatableC<plMessage>(S));
    else
        setEndMessage(nullptr);

    fFadeIn = S->readFloat();
    fFadeOut = S->readFloat();
    fMoveMode = (MoveMode)S->readByte();
    fBodyUsage = (plAGAnim::BodyUsage)S->readByte();
    fRecipient = mgr->readKey(S);
}

void plAvBrainGeneric::write(hsStream* S, plResManager* mgr)
{
    plArmatureBrain::write(S, mgr);

    S->writeInt(fStages.size());
    for (size_t i=0; i<fStages.size(); i++) {
        mgr->WriteCreatable(S, fStages[i]);
        fStages[i]->writeAux(S);
    }

    S->writeInt(fCurStage);
    S->writeInt(fType);
    S->writeInt(fExitFlags);
    S->writeByte(fMode);
    S->writeBool(fForward);

    S->writeBool(fStartMessage != nullptr);
    if (fStartMessage)
        mgr->WriteCreatable(S, fStartMessage);

    S->writeBool(fEndMessage != nullptr);
    if (fEndMessage)
        mgr->WriteCreatable(S, fEndMessage);

    S->writeFloat(fFadeIn);
    S->writeFloat(fFadeOut);
    S->writeByte(fMoveMode);
    S->writeByte(fBodyUsage);
    mgr->writeKey(S, fRecipient);
}

void plAvBrainGeneric::IPrcWrite(pfPrcHelper* prc)
{
    plArmatureBrain::IPrcWrite(prc);

    prc->startTag("Stages");
    prc->writeParam("Current", fCurStage);
    prc->endTag();
    for (size_t i=0; i<fStages.size(); i++) {
        prc->writeSimpleTag("Stage");
        fStages[i]->prcWrite(prc);
        fStages[i]->prcWriteAux(prc);
        prc->closeTag();
    }
    prc->closeTag();

    prc->startTag("AvBrainGenericParams");
    prc->writeParam("Type", fType);
    prc->writeParamHex("ExitFlags", fExitFlags);
    prc->writeParam("Mode", fMode);
    prc->writeParam("Forward", fForward);
    prc->writeParam("FadeIn", fFadeIn);
    prc->writeParam("FadeOut", fFadeOut);
    prc->writeParam("MoveMode", fMoveMode);
    prc->writeParam("BodyUsage", fBodyUsage);
    prc->endTag(true);

    if (fStartMessage) {
        prc->writeSimpleTag("StartMessage");
        fStartMessage->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("StartMessage");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }

    if (fEndMessage) {
        prc->writeSimpleTag("EndMessage");
        fEndMessage->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("EndMessage");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }

    prc->writeSimpleTag("Recipient");
    plResManager::PrcWriteKey(prc, fRecipient);
    prc->closeTag();
}

void plAvBrainGeneric::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Stages") {
        fCurStage = tag->getParam("Current", "0").to_int();
        clearStages();
        fStages.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStages.size(); i++) {
            if (child->getName() != "Stage")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            const pfPrcTag* stageChild = child->getFirstChild();
            while (stageChild) {
                fStages[i] = new plAnimStage();
                if (stageChild->getName() == "plAnimStage") {
                    fStages[i]->prcParse(stageChild, mgr);
                } else if (stageChild->getName() == "plAnimStage_Aux") {
                    fStages[i]->prcParseAux(stageChild);
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, stageChild->getName());
                }
                stageChild = stageChild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "AvBrainGenericParams") {
        fType = (BrainType)tag->getParam("Type", "0").to_uint();
        fExitFlags = tag->getParam("ExitFlags", "0").to_uint();
        fMode = (Mode)tag->getParam("Mode", "0").to_uint();
        fForward = tag->getParam("Forward", "False").to_bool();
        fFadeIn = tag->getParam("FadeIn", "0").to_float();
        fFadeOut = tag->getParam("FadeOut", "0").to_float();
        fMoveMode = (MoveMode)tag->getParam("MoveMode", "0").to_uint();
        fBodyUsage = (plAGAnim::BodyUsage)tag->getParam("BodyUsage", "0").to_uint();
    } else if (tag->getName() == "StartMessage") {
        if (tag->getParam("NULL", "False").to_bool()) {
            setStartMessage(nullptr);
        } else if (tag->hasChildren()) {
            setStartMessage(mgr->prcParseCreatableC<plMessage>(tag->getFirstChild()));
        }
    } else if (tag->getName() == "EndMessage") {
        if (tag->getParam("NULL", "False").to_bool()) {
            setEndMessage(nullptr);
        } else if (tag->hasChildren()) {
            setEndMessage(mgr->prcParseCreatableC<plMessage>(tag->getFirstChild()));
        }
    } else if (tag->getName() == "Recipient") {
        if (tag->hasChildren())
            fRecipient = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plArmatureBrain::IPrcParse(tag, mgr);
    }
}

void plAvBrainGeneric::delStage(size_t idx)
{
    delete fStages[idx];
    fStages.erase(fStages.begin() + idx);
}

void plAvBrainGeneric::clearStages()
{
    for (auto stage = fStages.begin(); stage != fStages.end(); ++stage)
        delete *stage;
    fStages.clear();
}

void plAvBrainGeneric::setStartMessage(plMessage* msg)
{
    delete fStartMessage;
    fStartMessage = msg;
}

void plAvBrainGeneric::setEndMessage(plMessage* msg)
{
    delete fEndMessage;
    fEndMessage = msg;
}
