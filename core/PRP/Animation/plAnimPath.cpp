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

#include "plAnimPath.h"

/* plAnimPath */
plAnimPath::~plAnimPath()
{
    delete fController;
    delete fTMController;
}

void plAnimPath::read(hsStream* S, plResManager* mgr)
{
    fAnimPathFlags = S->readInt();

    delete fController;
    delete fTMController;

    bool useTM = S->getVer().isUruSP();
    if (S->getVer().isUniversal())
        useTM = S->readBool();

    if (useTM) {
        fTMController = new plTMController();
        fTMController->read(S, mgr);
        fController = nullptr;
    } else {
        fController = mgr->ReadCreatableC<plCompoundController>(S);
        fTMController = nullptr;
    }

    fParts.read(S);
    fLocalToWorld.read(S);
    fWorldToLocal.read(S);
    fLength = S->readFloat();
    fMinDistSq = S->readFloat();
}

void plAnimPath::write(hsStream* S, plResManager* mgr)
{
    S->writeInt(fAnimPathFlags);

    bool useTM = S->getVer().isUruSP();
    if (S->getVer().isUniversal()) {
        useTM = (fTMController != nullptr);
        S->writeBool(useTM);
    }

    if (useTM) {
        plTMController* controller = fTMController;
        if (controller == nullptr && fController != nullptr)
            controller = fController->convertToTMController();
        if (controller == nullptr) {
            controller = new plTMController();
            controller->write(S, mgr);
            delete controller;
        } else {
            controller->write(S, mgr);
        }
    } else {
        plCompoundController* controller = fController;
        if (controller == nullptr && fTMController != nullptr)
            controller = fTMController->convertToCompoundController();
        mgr->WriteCreatable(S, controller);
    }

    fParts.write(S);
    fLocalToWorld.write(S);
    fWorldToLocal.write(S);
    S->writeFloat(fLength);
    S->writeFloat(fMinDistSq);
}

void plAnimPath::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("AnimPathParams");
      prc->writeParamHex("Flags", fAnimPathFlags);
      prc->writeParam("Length", fLength);
      prc->writeParam("MinDistSq", fMinDistSq);
    prc->endTag(true);

    prc->writeSimpleTag("Controller");
    if (fController)
        fController->prcWrite(prc);
    if (fTMController)
        fTMController->prcWrite(prc);
    prc->closeTag();
    fParts.prcWrite(prc);

    prc->writeSimpleTag("LocalToWorld");
      fLocalToWorld.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLocal");
      fWorldToLocal.prcWrite(prc);
    prc->closeTag();
}

void plAnimPath::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "AnimPathParams") {
        fAnimPathFlags = tag->getParam("Flags", "0").to_uint();
        fLength = tag->getParam("Length", "0").to_float();
        fMinDistSq = tag->getParam("MinDistSq", "0").to_float();
    } else if (tag->getName() == "Controller") {
        if (tag->hasChildren()) {
            delete fController;
            delete fTMController;
            if (tag->getFirstChild()->getName() == "plTMController") {
                fTMController = new plTMController();
                fTMController->prcParse(tag->getFirstChild(), mgr);
                fController = nullptr;
            } else {
                fController = mgr->prcParseCreatableC<plCompoundController>(tag->getFirstChild());
                fTMController = nullptr;
            }
        }
    } else if (tag->getName() == "hsAffineParts") {
        fParts.prcParse(tag);
    } else if (tag->getName() == "LocalToWorld") {
        if (tag->hasChildren())
            fLocalToWorld.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldToLocal") {
        if (tag->hasChildren())
            fWorldToLocal.prcParse(tag->getFirstChild());
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plAnimPath::setController(plCompoundController* controller)
{
    delete fController;
    delete fTMController;
    fController = controller;
    fTMController = nullptr;
}

void plAnimPath::setTMController(plTMController* controller)
{
    delete fController;
    delete fTMController;
    fTMController = controller;
    fController = nullptr;
}
