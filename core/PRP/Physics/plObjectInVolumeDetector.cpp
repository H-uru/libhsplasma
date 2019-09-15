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

#include "plObjectInVolumeDetector.h"

/* plCameraRegionDetector */
plCameraRegionDetector::~plCameraRegionDetector()
{
    for (auto msg = fMessages.begin(); msg != fMessages.end(); ++msg)
        delete *msg;
}

void plCameraRegionDetector::read(hsStream* S, plResManager* mgr)
{
    plDetectorModifier::read(S, mgr);

    clearMessages();
    fMessages.resize(S->readInt());
    for (size_t i=0; i<fMessages.size(); i++)
        fMessages[i] = mgr->ReadCreatableC<plCameraMsg>(S);
}

void plCameraRegionDetector::write(hsStream* S, plResManager* mgr)
{
    plDetectorModifier::write(S, mgr);

    S->writeInt(fMessages.size());
    for (size_t i=0; i<fMessages.size(); i++)
        mgr->WriteCreatable(S, fMessages[i]);
}

void plCameraRegionDetector::IPrcWrite(pfPrcHelper* prc)
{
    plDetectorModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Messages");
    for (size_t i=0; i<fMessages.size(); i++)
        fMessages[i]->prcWrite(prc);
    prc->closeTag();
}

void plCameraRegionDetector::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Messages") {
        clearMessages();
        fMessages.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMessages.size(); i++) {
            fMessages[i] = mgr->prcParseCreatableC<plCameraMsg>(child);
            child = child->getNextSibling();
        }
    } else {
        plDetectorModifier::IPrcParse(tag, mgr);
    }
}

void plCameraRegionDetector::delMessage(size_t idx)
{
    delete fMessages[idx];
    fMessages.erase(fMessages.begin() + idx);
}

void plCameraRegionDetector::clearMessages()
{
    for (auto msg = fMessages.begin(); msg != fMessages.end(); ++msg)
        delete *msg;
    fMessages.clear();
}


/* plObjectInVolumeAndFacingDetector */
void plObjectInVolumeAndFacingDetector::read(hsStream* S, plResManager* mgr)
{
    plObjectInVolumeDetector::read(S, mgr);
    fFacingTolerance = S->readFloat();
    fNeedWalkingForward = S->readBool();
}

void plObjectInVolumeAndFacingDetector::write(hsStream* S, plResManager* mgr)
{
    plObjectInVolumeDetector::write(S, mgr);
    S->writeFloat(fFacingTolerance);
    S->writeBool(fNeedWalkingForward);
}

void plObjectInVolumeAndFacingDetector::IPrcWrite(pfPrcHelper* prc)
{
    plObjectInVolumeDetector::IPrcWrite(prc);

    prc->startTag("FacingParams");
    prc->writeParam("Tolerance", fFacingTolerance);
    prc->writeParam("NeedWalkingForward", fNeedWalkingForward);
    prc->endTag(true);
}

void plObjectInVolumeAndFacingDetector::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "FacingParams") {
        fFacingTolerance = tag->getParam("Tolerance", "0").to_float();
        fNeedWalkingForward = tag->getParam("NeedWalkingForward", "false").to_bool();
    } else {
        plObjectInVolumeDetector::IPrcParse(tag, mgr);
    }
}
