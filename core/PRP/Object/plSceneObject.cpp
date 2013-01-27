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

#include "plSceneObject.h"
#include "PRP/Modifier/plModifier.h"

void plSceneObject::addTarget(hsKeyedObject* obj) {
    if (obj->isStub()) {
        fputs("WARNING:  Adding STUB modifier to SceneObject\n", stderr);
        return;
    }

    plModifier* mod = plModifier::Convert(obj);
    mod->addTarget(getKey());
}

void plSceneObject::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    fDrawIntf = mgr->readKey(S);
    fSimIntf = mgr->readKey(S);
    fCoordIntf = mgr->readKey(S);
    fAudioIntf = mgr->readKey(S);

    fInterfaces.resize(S->readInt());
    for (size_t i=0; i<fInterfaces.size(); i++)
        fInterfaces[i] = mgr->readKey(S);
    fModifiers.resize(S->readInt());
    for (size_t i=0; i<fModifiers.size(); i++) {
        fModifiers[i] = mgr->readKeyNotify(S,
            std::bind(&plSceneObject::addTarget, this, std::placeholders::_1));
    }

    fSceneNode = mgr->readKey(S);
}

void plSceneObject::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);

    mgr->writeKey(S, fDrawIntf);
    mgr->writeKey(S, fSimIntf);
    mgr->writeKey(S, fCoordIntf);
    mgr->writeKey(S, fAudioIntf);

    S->writeInt(fInterfaces.size());
    for (size_t i=0; i<fInterfaces.size(); i++)
        mgr->writeKey(S, fInterfaces[i]);
    S->writeInt(fModifiers.size());
    for (size_t i=0; i<fModifiers.size(); i++)
        mgr->writeKey(S, fModifiers[i]);
    mgr->writeKey(S, fSceneNode);
}

void plSceneObject::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("DrawInterface");
      fDrawIntf->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SimulationInterface");
      fSimIntf->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("CoordinateInterface");
      fCoordIntf->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("AudioInterface");
      fAudioIntf->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Interfaces");
    for (size_t i=0; i<fInterfaces.size(); i++)
        fInterfaces[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Modifiers");
    for (size_t i=0; i<fModifiers.size(); i++)
        fModifiers[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SceneNode");
      fSceneNode->prcWrite(prc);
    prc->closeTag();
}

void plSceneObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DrawInterface") {
        if (tag->hasChildren())
            fDrawIntf = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SimulationInterface") {
        if (tag->hasChildren())
            fSimIntf = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "CoordinateInterface") {
        if (tag->hasChildren())
            fCoordIntf = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "AudioInterface") {
        if (tag->hasChildren())
            fAudioIntf = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Interfaces") {
        fInterfaces.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fInterfaces.size(); i++) {
            fInterfaces[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Modifiers") {
        fModifiers.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fModifiers.size(); i++) {
            fModifiers[i] = mgr->prcParseKeyNotify(child,
                std::bind(&plSceneObject::addTarget, this, std::placeholders::_1));
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}

void plSceneObject::addModifier(plKey intf) {
    fModifiers.push_back(intf);
    intf->addCallback(std::bind(&plSceneObject::addTarget, this, std::placeholders::_1));
}

void plSceneObject::delModifier(size_t idx) {
    plKey key = fModifiers[idx];
    fModifiers.erase(fModifiers.begin() + idx);

    if (key.isLoaded()) {
        if (key->getObj()->isStub()) {
            fputs("WARNING:  Removing STUB modifier from SceneObject\n", stderr);
        } else {
            plModifier* mod = plModifier::Convert(key->getObj());
            mod->removeTarget(getKey());
        }
    }
}

void plSceneObject::clearModifiers() {
    for (size_t i = 0; i < fModifiers.size(); i++) {
        plKey key = fModifiers[i];
        if (key.isLoaded()) {
            if (key->getObj()->isStub()) {
                fputs("WARNING:  Removing STUB modifier from SceneObject\n", stderr);
                continue;
            }
            plModifier* mod = plModifier::Convert(key->getObj(), false);
            mod->removeTarget(getKey());
        }
    }

    fModifiers.clear();
}
