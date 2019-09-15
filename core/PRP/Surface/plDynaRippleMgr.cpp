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

#include "plDynaRippleMgr.h"

/* plDynaRippleMgr */
void plDynaRippleMgr::read(hsStream* S, plResManager* mgr)
{
    plDynaDecalMgr::read(S, mgr);
    fInitUVW.read(S);
    fFinalUVW.read(S);
}

void plDynaRippleMgr::write(hsStream* S, plResManager* mgr)
{
    plDynaDecalMgr::write(S, mgr);
    fInitUVW.write(S);
    fFinalUVW.write(S);
}

void plDynaRippleMgr::IPrcWrite(pfPrcHelper* prc)
{
    plDynaDecalMgr::IPrcWrite(prc);

    prc->writeSimpleTag("InitUVW");
    fInitUVW.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("FinalUVW");
    fFinalUVW.prcWrite(prc);
    prc->closeTag();
}

void plDynaRippleMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "InitUVW") {
        if (tag->hasChildren())
            fInitUVW.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "FinalUVW") {
        if (tag->hasChildren())
            fFinalUVW.prcParse(tag->getFirstChild());
    } else {
        plDynaDecalMgr::IPrcParse(tag, mgr);
    }
}


/* plDynaRippleVSMgr */
void plDynaRippleVSMgr::read(hsStream* S, plResManager* mgr)
{
    plDynaRippleMgr::read(S, mgr);
    fWaveSetBase = mgr->readKey(S);
}

void plDynaRippleVSMgr::write(hsStream* S, plResManager* mgr)
{
    plDynaRippleMgr::write(S, mgr);
    mgr->writeKey(S, fWaveSetBase);
}

void plDynaRippleVSMgr::IPrcWrite(pfPrcHelper* prc)
{
    plDynaRippleMgr::IPrcWrite(prc);

    prc->writeSimpleTag("WaveSet");
    plResManager::PrcWriteKey(prc, fWaveSetBase);
    prc->closeTag();
}

void plDynaRippleVSMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "WaveSet") {
        if (tag->hasChildren())
            fWaveSetBase = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plDynaRippleMgr::IPrcParse(tag, mgr);
    }
}


/* plDynaTorpedoVSMgr */
void plDynaTorpedoVSMgr::read(hsStream* S, plResManager* mgr)
{
    plDynaTorpedoMgr::read(S, mgr);
    fWaveSetBase = mgr->readKey(S);
}

void plDynaTorpedoVSMgr::write(hsStream* S, plResManager* mgr)
{
    plDynaTorpedoMgr::write(S, mgr);
    mgr->writeKey(S, fWaveSetBase);
}

void plDynaTorpedoVSMgr::IPrcWrite(pfPrcHelper* prc)
{
    plDynaTorpedoMgr::IPrcWrite(prc);

    prc->writeSimpleTag("WaveSet");
    plResManager::PrcWriteKey(prc, fWaveSetBase);
    prc->closeTag();
}

void plDynaTorpedoVSMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "WaveSet") {
        if (tag->hasChildren())
            fWaveSetBase = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plDynaRippleMgr::IPrcParse(tag, mgr);
    }
}


/* plDynaWakeMgr */
plDynaWakeMgr::~plDynaWakeMgr()
{
    delete fAnimPath;
}

void plDynaWakeMgr::read(hsStream* S, plResManager* mgr)
{
    plDynaRippleMgr::read(S, mgr);

    fDefaultDir.read(S);
    setAnimPath(mgr->ReadCreatableC<plAnimPath>(S));
    fAnimWgt = S->readFloat();
    fVelWgt = S->readFloat();
}

void plDynaWakeMgr::write(hsStream* S, plResManager* mgr)
{
    plDynaRippleMgr::write(S, mgr);

    fDefaultDir.write(S);
    mgr->WriteCreatable(S, fAnimPath);
    S->writeFloat(fAnimWgt);
    S->writeFloat(fVelWgt);
}

void plDynaWakeMgr::IPrcWrite(pfPrcHelper* prc)
{
    plDynaRippleMgr::IPrcWrite(prc);

    prc->writeSimpleTag("DefaultDir");
    fDefaultDir.prcWrite(prc);
    prc->closeTag();

    prc->startTag("DynaWakeMgrParams");
    prc->writeParam("AnimWeight", fAnimWgt);
    prc->writeParam("VelWeight", fVelWgt);
    prc->endTag(true);

    if (fAnimPath) {
        fAnimPath->prcWrite(prc);
    } else {
        prc->startTag("plAnimPath");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plDynaWakeMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "DefaultDir") {
        if (tag->hasChildren())
            fDefaultDir.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "DynaWakeMgrParams") {
        fAnimWgt = tag->getParam("AnimWeight", "0").to_float();
        fVelWgt = tag->getParam("VelWeight", "0").to_float();
    } else if (tag->getName() == "plAnimPath") {
        if (tag->getParam("NULL", "false").to_bool()) {
            setAnimPath(nullptr);
        } else {
            if (tag->hasChildren())
                setAnimPath(mgr->prcParseCreatableC<plAnimPath>(tag->getFirstChild()));
        }
    } else {
        plDynaRippleMgr::IPrcParse(tag, mgr);
    }
}

void plDynaWakeMgr::setAnimPath(plAnimPath* path)
{
    delete fAnimPath;
    fAnimPath = path;
}
