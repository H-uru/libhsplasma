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

#include "plParticleSystem.h"

plParticleSystem::~plParticleSystem()
{
    for (auto emitter : fEmitters)
        delete emitter;
    delete fAmbientCtl;
    delete fDiffuseCtl;
    delete fOpacityCtl;
    delete fWidthCtl;
    delete fHeightCtl;
}

void plParticleSystem::read(hsStream* S, plResManager* mgr)
{
    plModifier::read(S, mgr);

    fMaterial = mgr->readKey(S);
    setAmbientCtl(mgr->ReadCreatableC<plController>(S));
    setDiffuseCtl(mgr->ReadCreatableC<plController>(S));
    setOpacityCtl(mgr->ReadCreatableC<plController>(S));
    setWidthCtl(mgr->ReadCreatableC<plController>(S));
    setHeightCtl(mgr->ReadCreatableC<plController>(S));

    fXTiles = S->readInt();
    fYTiles = S->readInt();
    fMaxTotalParticles = S->readInt();
    uint32_t maxEmitters = S->readInt();
    fPreSim = S->readFloat();
    fAccel.read(S);
    fDrag = S->readFloat();
    fWindMult = S->readFloat();
    fNumValidEmitters = S->readInt();

    for (auto emitter : fEmitters)
        delete emitter;
    fEmitters.resize(maxEmitters, nullptr);
    if (fNumValidEmitters > maxEmitters)
        throw hsBadParamException(__FILE__, __LINE__);
    for (size_t i=0; i<fNumValidEmitters; i++)
        fEmitters[i] = mgr->ReadCreatableC<plParticleEmitter>(S);

    fForces.resize(S->readInt());
    for (size_t i=0; i<fForces.size(); i++)
        fForces[i] = mgr->readKey(S);
    fEffects.resize(S->readInt());
    for (size_t i=0; i<fEffects.size(); i++)
        fEffects[i] = mgr->readKey(S);
    fConstraints.resize(S->readInt());
    for (size_t i=0; i<fConstraints.size(); i++)
        fConstraints[i] = mgr->readKey(S);

    fPermaLights.resize(S->readInt());
    for (size_t i=0; i<fPermaLights.size(); i++)
        fPermaLights[i] = mgr->readKey(S);
}

void plParticleSystem::write(hsStream* S, plResManager* mgr)
{
    plSynchedObject::write(S, mgr);

    mgr->writeKey(S, fMaterial);
    mgr->WriteCreatable(S, fAmbientCtl);
    mgr->WriteCreatable(S, fDiffuseCtl);
    mgr->WriteCreatable(S, fOpacityCtl);
    mgr->WriteCreatable(S, fWidthCtl);
    mgr->WriteCreatable(S, fHeightCtl);

    S->writeInt(fXTiles);
    S->writeInt(fYTiles);
    S->writeInt(fMaxTotalParticles);
    S->writeInt(fEmitters.size());
    S->writeFloat(fPreSim);
    fAccel.write(S);
    S->writeFloat(fDrag);
    S->writeFloat(fWindMult);

    if (fNumValidEmitters > fEmitters.size()) {
        throw hsBadParamException(__FILE__, __LINE__,
                "Cannot have more valid emitters than total emitters");
    }
    S->writeInt(fNumValidEmitters);
    for (size_t i=0; i<fNumValidEmitters; i++)
        mgr->WriteCreatable(S, fEmitters[i]);

    S->writeInt(fForces.size());
    for (size_t i=0; i<fForces.size(); i++)
        mgr->writeKey(S, fForces[i]);
    S->writeInt(fEffects.size());
    for (size_t i=0; i<fEffects.size(); i++)
        mgr->writeKey(S, fEffects[i]);
    S->writeInt(fConstraints.size());
    for (size_t i=0; i<fConstraints.size(); i++)
        mgr->writeKey(S, fConstraints[i]);

    S->writeInt(fPermaLights.size());
    for (size_t i=0; i<fPermaLights.size(); i++)
        mgr->writeKey(S, fPermaLights[i]);
}

void plParticleSystem::IPrcWrite(pfPrcHelper* prc)
{
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Material");
    plResManager::PrcWriteKey(prc, fMaterial);
    prc->closeTag();

    if (fAmbientCtl) {
        prc->writeSimpleTag("AmbientCtl");
        fAmbientCtl->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("AmbientCtl");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fDiffuseCtl) {
        prc->writeSimpleTag("DiffuseCtl");
        fDiffuseCtl->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("DiffuseCtl");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fOpacityCtl) {
        prc->writeSimpleTag("OpacityCtl");
        fOpacityCtl->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("OpacityCtl");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fWidthCtl) {
        prc->writeSimpleTag("WidthCtl");
        fWidthCtl->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("WidthCtl");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    if (fHeightCtl) {
        prc->writeSimpleTag("HeightCtl");
        fHeightCtl->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("HeightCtl");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }

    prc->startTag("ParticleParams");
    prc->writeParam("XTiles", fXTiles);
    prc->writeParam("YTiles", fYTiles);
    prc->writeParam("MaxTotalParticles", fMaxTotalParticles);
    prc->writeParam("MaxEmitters", fEmitters.size());
    prc->writeParam("PreSim", fPreSim);
    prc->writeParam("Drag", fDrag);
    prc->writeParam("WindMult", fWindMult);
    prc->endTag(true);

    prc->writeSimpleTag("Accel");
    fAccel.prcWrite(prc);
    prc->closeTag();

    if (fNumValidEmitters > fEmitters.size()) {
        throw hsBadParamException(__FILE__, __LINE__,
                "Cannot have more valid emitters than total emitters");
    }
    prc->writeSimpleTag("Emitters");
    for (size_t i=0; i<fNumValidEmitters; i++)
        fEmitters[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Forces");
    for (size_t i=0; i<fForces.size(); i++)
        plResManager::PrcWriteKey(prc, fForces[i]);
    prc->closeTag();
    prc->writeSimpleTag("Effects");
    for (size_t i=0; i<fEffects.size(); i++)
        plResManager::PrcWriteKey(prc, fEffects[i]);
    prc->closeTag();
    prc->writeSimpleTag("Constraints");
    for (size_t i=0; i<fConstraints.size(); i++)
        plResManager::PrcWriteKey(prc, fConstraints[i]);
    prc->closeTag();

    prc->writeSimpleTag("PermaLights");
    for (size_t i=0; i<fPermaLights.size(); i++)
        plResManager::PrcWriteKey(prc, fPermaLights[i]);
    prc->closeTag();
}

void plParticleSystem::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Material") {
        if (tag->hasChildren())
            fMaterial = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "AmbientCtl") {
        if (tag->hasChildren() && !tag->getParam("NULL", "false").to_bool())
            setAmbientCtl(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else if (tag->getName() == "DiffuseCtl") {
        if (tag->hasChildren() && !tag->getParam("NULL", "false").to_bool())
            setDiffuseCtl(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else if (tag->getName() == "OpacityCtl") {
        if (tag->hasChildren() && !tag->getParam("NULL", "false").to_bool())
            setOpacityCtl(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else if (tag->getName() == "WidthCtl") {
        if (tag->hasChildren() && !tag->getParam("NULL", "false").to_bool())
            setWidthCtl(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else if (tag->getName() == "HeightCtl") {
        if (tag->hasChildren() && !tag->getParam("NULL", "false").to_bool())
            setHeightCtl(mgr->prcParseCreatableC<plController>(tag->getFirstChild()));
    } else if (tag->getName() == "ParticleParams") {
        fXTiles = tag->getParam("XTiles", "0").to_uint();
        fYTiles = tag->getParam("YTiles", "0").to_uint();
        fMaxTotalParticles = tag->getParam("MaxTotalParticles", "0").to_uint();
        uint32_t maxEmitters = tag->getParam("MaxEmitters", "0").to_uint();
        for (auto emitter : fEmitters)
            delete emitter;
        fEmitters.resize(maxEmitters, nullptr);
        fPreSim = tag->getParam("PreSim", "0").to_float();
        fDrag = tag->getParam("Drag", "0").to_float();
        fWindMult = tag->getParam("WindMult", "0").to_float();
    } else if (tag->getName() == "Accel") {
        if (tag->hasChildren())
            fAccel.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Emitters") {
        fNumValidEmitters = tag->countChildren();
        if (fNumValidEmitters > fEmitters.size())
            throw pfPrcParseException(__FILE__, __LINE__, "Too many particle emitters");
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fNumValidEmitters; i++) {
            fEmitters[i] = mgr->prcParseCreatableC<plParticleEmitter>(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Forces") {
        fForces.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fForces.size(); i++) {
            fForces[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Effects") {
        fEffects.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fEffects.size(); i++) {
            fEffects[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Constraints") {
        fConstraints.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fConstraints.size(); i++) {
            fConstraints[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "PermaLights") {
        fPermaLights.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fPermaLights.size(); i++) {
            fPermaLights[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}

void plParticleSystem::setAmbientCtl(plController* ctl)
{
    delete fAmbientCtl;
    fAmbientCtl = ctl;
}

void plParticleSystem::setDiffuseCtl(plController* ctl)
{
    delete fDiffuseCtl;
    fDiffuseCtl = ctl;
}

void plParticleSystem::setOpacityCtl(plController* ctl)
{
    delete fOpacityCtl;
    fOpacityCtl = ctl;
}

void plParticleSystem::setWidthCtl(plController* ctl)
{
    delete fWidthCtl;
    fWidthCtl = ctl;
}

void plParticleSystem::setHeightCtl(plController* ctl)
{
    delete fHeightCtl;
    fHeightCtl = ctl;
}

void plParticleSystem::allocEmitters(size_t max)
{
    for (size_t i = max; i < fEmitters.size(); ++i) {
        // When max < fEmitters.size()
        delete fEmitters[i];
    }
    fEmitters.resize(max, nullptr);
    if (fNumValidEmitters > max)
        fNumValidEmitters = max;
}

void plParticleSystem::setEmitter(size_t idx, plParticleEmitter* emitter)
{
    delete fEmitters[idx];
    fEmitters[idx] = emitter;
}

void plParticleSystem::addEmitter(plParticleEmitter* emitter)
{
    fNumValidEmitters++;
    if (fNumValidEmitters > fEmitters.size())
        fEmitters.resize(fNumValidEmitters);
    fEmitters[fNumValidEmitters - 1] = emitter;
}

void plParticleSystem::delEmitter(size_t idx)
{
    delete fEmitters[idx];
    for (size_t i = idx; i < fEmitters.size() - 1; ++i)
        fEmitters[i] = fEmitters[i + 1];
    fEmitters[fEmitters.size() - 1] = nullptr;
    fNumValidEmitters--;
}

void plParticleSystem::clearEmitters()
{
    for (auto emitter : fEmitters)
        delete emitter;
    fEmitters.clear();
    fNumValidEmitters = 0;
}
