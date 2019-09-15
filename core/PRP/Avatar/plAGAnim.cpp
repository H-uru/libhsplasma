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

#include "plAGAnim.h"

/* plAGAnim */
plAGAnim::~plAGAnim()
{
    for (auto app = fApps.begin(); app != fApps.end(); ++app)
        delete *app;
}

void plAGAnim::read(hsStream* S, plResManager* mgr)
{
    plSynchedObject::read(S, mgr);

    fName = S->readSafeStr();
    fStart = S->readFloat();
    fEnd = S->readFloat();

    clearApplicators();
    fApps.resize(S->readInt());
    for (size_t i=0; i<fApps.size(); i++) {
        auto agApp = mgr->ReadCreatableC<plAGApplicator>(S);
        auto agChan = mgr->ReadCreatableC<plAGChannel>(S);
        agApp->setChannel(agChan);
        fApps[i] = agApp;
    }

    if (S->getVer().isNewPlasma())
        fEoaFlag = S->readByte();
}

void plAGAnim::write(hsStream* S, plResManager* mgr)
{
    plSynchedObject::write(S, mgr);

    S->writeSafeStr(fName);
    S->writeFloat(fStart);
    S->writeFloat(fEnd);

    S->writeInt(fApps.size());
    for (size_t i=0; i<fApps.size(); i++) {
        mgr->WriteCreatable(S, fApps[i]);
        mgr->WriteCreatable(S, fApps[i]->getChannel());
    }

    if (S->getVer().isNewPlasma())
        S->writeByte(fEoaFlag);
}

void plAGAnim::IPrcWrite(pfPrcHelper* prc)
{
    plSynchedObject::IPrcWrite(prc);

    prc->startTag("AGAnimParams");
    prc->writeParam("Name", fName);
    prc->writeParam("Start", fStart);
    prc->writeParam("End", fEnd);
    prc->writeParam("EoaFlag", fEoaFlag);
    prc->endTag(true);

    prc->writeSimpleTag("Applicators");
    for (size_t i=0; i<fApps.size(); i++) {
        prc->writeSimpleTag("AppSet");
          prc->writeSimpleTag("Applicator");
          fApps[i]->prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("Channel");
          fApps[i]->getChannel()->prcWrite(prc);
          prc->closeTag();
        prc->closeTag();
    }
    prc->closeTag();
}

void plAGAnim::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "AGAnimParams") {
        fName = tag->getParam("Name", "");
        fStart = tag->getParam("Start", "0").to_float();
        fEnd = tag->getParam("End", "0").to_float();
        fEoaFlag = tag->getParam("EoaFlag", "0").to_uint();
    } else if (tag->getName() == "Applicators") {
        clearApplicators();
        fApps.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fApps.size(); i++) {
            if (child->getName() != "AppSet")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());

            const pfPrcTag* subChild = child->getFirstChild();
            plAGApplicator* agApp = nullptr;
            plAGChannel* agChan = nullptr;
            while (subChild) {
                if (subChild->getName() == "Applicator") {
                    if (subChild->hasChildren())
                        agApp = mgr->prcParseCreatableC<plAGApplicator>(subChild->getFirstChild());
                } else if (subChild->getName() == "Channel") {
                    if (subChild->hasChildren())
                        agChan = mgr->prcParseCreatableC<plAGChannel>(subChild->getFirstChild());
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                }
                subChild = subChild->getNextSibling();
            }
            if (agApp == nullptr)
                throw pfPrcParseException(__FILE__, __LINE__, "Missing Applicator");
            agApp->setChannel(agChan);
            fApps[i] = agApp;
            child = child->getNextSibling();
        }
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}

void plAGAnim::clearApplicators()
{
    for (auto app = fApps.begin(); app != fApps.end(); ++app)
        delete *app;
    fApps.clear();
}

void plAGAnim::delApplicator(size_t idx)
{
    delete fApps[idx];
    fApps.erase(fApps.begin() + idx);
}


/* plAgeGlobalAnim */
void plAgeGlobalAnim::read(hsStream* S, plResManager* mgr)
{
    plAGAnim::read(S, mgr);
    fGlobalVarName = S->readSafeStr();
}

void plAgeGlobalAnim::write(hsStream* S, plResManager* mgr)
{
    plAGAnim::write(S, mgr);
    S->writeSafeStr(fGlobalVarName);
}

void plAgeGlobalAnim::IPrcWrite(pfPrcHelper* prc)
{
    plAGAnim::IPrcWrite(prc);

    prc->startTag("AgeGlobalAnimParams");
    prc->writeParam("GlobalVarName", fGlobalVarName);
    prc->endTag(true);
}

void plAgeGlobalAnim::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "AgeGlobalAnimParams") {
        fGlobalVarName = tag->getParam("GlobalVarName", "");
    } else {
        plAGAnim::IPrcParse(tag, mgr);
    }
}
