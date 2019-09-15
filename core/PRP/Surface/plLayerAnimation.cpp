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

#include "plLayerAnimation.h"

/* plLayerAnimationBase */
plLayerAnimationBase::~plLayerAnimationBase()
{
    delete fPreshadeColorCtl;
    delete fRuntimeColorCtl;
    delete fAmbientColorCtl;
    delete fSpecularColorCtl;
    delete fOpacityCtl;
    delete fTransformCtl;
}

void plLayerAnimationBase::read(hsStream* S, plResManager* mgr)
{
    plLayerInterface::read(S, mgr);

    setPreshadeCtl(mgr->ReadCreatableC<plController>(S));
    setRuntimeCtl(mgr->ReadCreatableC<plController>(S));
    setAmbientCtl(mgr->ReadCreatableC<plController>(S));
    setSpecularCtl(mgr->ReadCreatableC<plController>(S));
    setOpacityCtl(mgr->ReadCreatableC<plController>(S));
    setTransformCtl(mgr->ReadCreatableC<plController>(S));
}

void plLayerAnimationBase::write(hsStream* S, plResManager* mgr)
{
    plLayerInterface::write(S, mgr);

    plController::WriteController(S, mgr, fPreshadeColorCtl);
    plController::WriteController(S, mgr, fRuntimeColorCtl);
    plController::WriteController(S, mgr, fAmbientColorCtl);
    plController::WriteController(S, mgr, fSpecularColorCtl);
    plController::WriteController(S, mgr, fOpacityCtl);
    plController::WriteController(S, mgr, fTransformCtl);
}

void plLayerAnimationBase::IPrcWrite(pfPrcHelper* prc)
{
    plLayerInterface::IPrcWrite(prc);

    if (fPreshadeColorCtl) {
        prc->writeSimpleTag("PreshadeColorCtl");
        fPreshadeColorCtl->prcWrite(prc);
        prc->closeTag();
    }
    if (fRuntimeColorCtl) {
        prc->writeSimpleTag("RuntimeColorCtl");
        fRuntimeColorCtl->prcWrite(prc);
        prc->closeTag();
    }
    if (fAmbientColorCtl) {
        prc->writeSimpleTag("AmbientColorCtl");
        fAmbientColorCtl->prcWrite(prc);
        prc->closeTag();
    }
    if (fSpecularColorCtl) {
        prc->writeSimpleTag("SpecularColorCtl");
        fSpecularColorCtl->prcWrite(prc);
        prc->closeTag();
    }
    if (fOpacityCtl) {
        prc->writeSimpleTag("OpacityCtl");
        fOpacityCtl->prcWrite(prc);
        prc->closeTag();
    }
    if (fTransformCtl) {
        prc->writeSimpleTag("TransformCtl");
        fTransformCtl->prcWrite(prc);
        prc->closeTag();
    }
}

void plLayerAnimationBase::prcParse(const pfPrcTag* tag, plResManager* mgr)
{
    plCreatable::prcParse(tag, mgr);
}

void plLayerAnimationBase::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "PreshadeColorCtl") {
        if (tag->hasChildren())
            setPreshadeCtl(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else if (tag->getName() == "RuntimeColorCtl") {
        if (tag->hasChildren())
            setRuntimeCtl(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else if (tag->getName() == "AmbientColorCtl") {
        if (tag->hasChildren())
            setAmbientCtl(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else if (tag->getName() == "SpecularColorCtl") {
        if (tag->hasChildren())
            setSpecularCtl(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else if (tag->getName() == "OpacityCtl") {
        if (tag->hasChildren())
            setOpacityCtl(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else if (tag->getName() == "TransformCtl") {
        if (tag->hasChildren())
            setTransformCtl(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else {
        plLayerInterface::IPrcParse(tag, mgr);
    }
}

void plLayerAnimationBase::setPreshadeCtl(plController* ctrl)
{
    delete fPreshadeColorCtl;
    fPreshadeColorCtl = ctrl;
}

void plLayerAnimationBase::setRuntimeCtl(plController* ctrl)
{
    delete fRuntimeColorCtl;
    fRuntimeColorCtl = ctrl;
}

void plLayerAnimationBase::setAmbientCtl(plController* ctrl)
{
    delete fAmbientColorCtl;
    fAmbientColorCtl = ctrl;
}

void plLayerAnimationBase::setSpecularCtl(plController* ctrl)
{
    delete fSpecularColorCtl;
    fSpecularColorCtl = ctrl;
}

void plLayerAnimationBase::setOpacityCtl(plController* ctrl)
{
    delete fOpacityCtl;
    fOpacityCtl = ctrl;
}

void plLayerAnimationBase::setTransformCtl(plController* ctrl)
{
    delete fTransformCtl;
    fTransformCtl = ctrl;
}


/* plLayerAnimation */
void plLayerAnimation::read(hsStream* S, plResManager* mgr)
{
    plLayerAnimationBase::read(S, mgr);
    fTimeConvert.read(S, mgr);
}

void plLayerAnimation::write(hsStream* S, plResManager* mgr)
{
    plLayerAnimationBase::write(S, mgr);
    fTimeConvert.write(S, mgr);
}

void plLayerAnimation::IPrcWrite(pfPrcHelper* prc)
{
    plLayerAnimationBase::IPrcWrite(prc);
    fTimeConvert.prcWrite(prc);
}

void plLayerAnimation::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "plAnimTimeConvert") {
        fTimeConvert.prcParse(tag, mgr);
    } else {
        plLayerAnimationBase::IPrcParse(tag, mgr);
    }
}


/* plLayerLinkAnimation */
void plLayerLinkAnimation::read(hsStream* S, plResManager* mgr)
{
    plLayerAnimation::read(S, mgr);

    fLinkKey = mgr->readKey(S);
    fLeavingAge = S->readBool();
}

void plLayerLinkAnimation::write(hsStream* S, plResManager* mgr)
{
    plLayerAnimation::write(S, mgr);

    mgr->writeKey(S, fLinkKey);
    S->writeBool(fLeavingAge);
}

void plLayerLinkAnimation::IPrcWrite(pfPrcHelper* prc)
{
    plLayerAnimation::IPrcWrite(prc);

    prc->startTag("LinkTo");
    prc->writeParam("LeavingAge", fLeavingAge);
    prc->endTag();
    plResManager::PrcWriteKey(prc, fLinkKey);
    prc->closeTag();
}

void plLayerLinkAnimation::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "LinkTo") {
        fLeavingAge = tag->getParam("LeavingAge", "false").to_bool();
        if (tag->hasChildren())
            fLinkKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plLayerAnimation::IPrcParse(tag, mgr);
    }
}


/* plLayerSDLAnimation */
void plLayerSDLAnimation::read(hsStream* S, plResManager* mgr)
{
    plLayerAnimationBase::read(S, mgr);
    fVarName = S->readSafeStr();
}

void plLayerSDLAnimation::write(hsStream* S, plResManager* mgr)
{
    plLayerAnimationBase::write(S, mgr);
    S->writeSafeStr(fVarName);
}

void plLayerSDLAnimation::IPrcWrite(pfPrcHelper* prc)
{
    plLayerAnimationBase::IPrcWrite(prc);

    prc->startTag("VarName");
    prc->writeParam("value", fVarName);
    prc->endTag(true);
}

void plLayerSDLAnimation::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "VarName") {
        fVarName = tag->getParam("value", "");
    } else {
        plLayerAnimationBase::IPrcParse(tag, mgr);
    }
}
