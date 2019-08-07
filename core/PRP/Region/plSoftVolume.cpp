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

#include "plSoftVolume.h"

/* plSoftVolume */
void plSoftVolume::read(hsStream* S, plResManager* mgr)
{
    plObjInterface::read(S, mgr);

    fListenState = S->readInt();
    fInsideStrength = S->readFloat();
    fOutsideStrength = S->readFloat();
}

void plSoftVolume::write(hsStream* S, plResManager* mgr)
{
    plObjInterface::write(S, mgr);

    S->writeInt(fListenState);
    S->writeFloat(fInsideStrength);
    S->writeFloat(fOutsideStrength);
}

void plSoftVolume::IPrcWrite(pfPrcHelper* prc)
{
    plObjInterface::IPrcWrite(prc);

    prc->startTag("SoftVolumeParams");
    prc->writeParam("ListenState", fListenState);
    prc->writeParam("InsideStrength", fInsideStrength);
    prc->writeParam("OutsideStrength", fOutsideStrength);
    prc->endTag(true);
}

void plSoftVolume::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SoftVolumeParams") {
        fListenState = tag->getParam("ListenState", "0").to_uint();
        fInsideStrength = tag->getParam("InsideStrength", "0").to_float();
        fOutsideStrength = tag->getParam("OutsideStrength", "0").to_float();
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}


/* plSoftVolumeSimple */
plSoftVolumeSimple::~plSoftVolumeSimple()
{
    delete fVolume;
}

void plSoftVolumeSimple::read(hsStream* S, plResManager* mgr)
{
    plSoftVolume::read(S, mgr);

    fSoftDist = S->readFloat();
    setVolume(mgr->ReadCreatableC<plVolumeIsect>(S));
}

void plSoftVolumeSimple::write(hsStream* S, plResManager* mgr)
{
    plSoftVolume::write(S, mgr);

    S->writeFloat(fSoftDist);
    mgr->WriteCreatable(S, fVolume);
}

void plSoftVolumeSimple::IPrcWrite(pfPrcHelper* prc)
{
    plSoftVolume::IPrcWrite(prc);

    prc->startTag("Volume");
    prc->writeParam("SoftDist", fSoftDist);
    if (fVolume == nullptr) {
        prc->writeParam("Null", true);
        prc->endTag(true);
    } else {
        prc->endTag();
        fVolume->prcWrite(prc);
        prc->closeTag();
    }
}

void plSoftVolumeSimple::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Volume") {
        fSoftDist = tag->getParam("SoftDist", "0").to_float();
        if (tag->hasChildren())
            setVolume(mgr->prcParseCreatableC<plVolumeIsect>(tag->getFirstChild()));
        else
            setVolume(nullptr);
    } else {
        plSoftVolume::IPrcParse(tag, mgr);
    }
}

void plSoftVolumeSimple::setVolume(plVolumeIsect* vol)
{
    delete fVolume;
    fVolume = vol;
}


/* plSoftVolumeComplex */
void plSoftVolumeComplex::read(hsStream* S, plResManager* mgr)
{
    plSoftVolume::read(S, mgr);

    fSubVolumes.resize(S->readInt());
    for (size_t i=0; i<fSubVolumes.size(); i++)
        fSubVolumes[i] = mgr->readKey(S);
}

void plSoftVolumeComplex::write(hsStream* S, plResManager* mgr)
{
    plSoftVolume::write(S, mgr);

    S->writeInt(fSubVolumes.size());
    for (size_t i=0; i<fSubVolumes.size(); i++)
        mgr->writeKey(S, fSubVolumes[i]);
}

void plSoftVolumeComplex::IPrcWrite(pfPrcHelper* prc)
{
    plSoftVolume::IPrcWrite(prc);

    prc->writeSimpleTag("SubVolumes");
    for (size_t i=0; i<fSubVolumes.size(); i++)
        plResManager::PrcWriteKey(prc, fSubVolumes[i]);
    prc->closeTag();
}

void plSoftVolumeComplex::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SubVolumes") {
        fSubVolumes.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSubVolumes.size(); i++) {
            fSubVolumes[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSoftVolume::IPrcParse(tag, mgr);
    }
}
