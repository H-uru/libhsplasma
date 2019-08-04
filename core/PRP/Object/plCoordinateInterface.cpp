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

#include "plCoordinateInterface.h"
#include "plSceneObject.h"

plCoordinateInterface::plCoordinateInterface()
{
    fLocalToParent.Reset();
    fParentToLocal.Reset();
    fLocalToWorld.Reset();
    fWorldToLocal.Reset();

    fProps.setName(kDisable, "kDisable");
    fProps.setName(kCanEverDelayTransform, "kCanEverDelayTransform");
    fProps.setName(kDelayedTransformEval, "kDelayedTransformEval");
}

static void _childCallback(plCoordinateInterface* self, hsKeyedObject* ko) {
    plCoordinateInterface* ci = plCoordinateInterface::Convert(ko);
    ci->setParent(self->getKey());
}

static void _setParentCallback(plCoordinateInterface* self, hsKeyedObject* ko)
{
    plSceneObject* child = plSceneObject::Convert(ko);
    plKey childCIkey = child->getCoordInterface();
    if (childCIkey.Exists())
        childCIkey->addCallback(std::bind(&_childCallback, self, std::placeholders::_1));
}

void plCoordinateInterface::read(hsStream* S, plResManager* mgr)
{
    plObjInterface::read(S, mgr);

    fLocalToParent.read(S);
    fParentToLocal.read(S);
    fLocalToWorld.read(S);
    fWorldToLocal.read(S);

    fChildren.resize(S->readInt());
    for (size_t i=0; i<fChildren.size(); i++) {
        fChildren[i] = mgr->readKeyNotify(S,
            std::bind(&_setParentCallback, this, std::placeholders::_1));
    }
}

void plCoordinateInterface::write(hsStream* S, plResManager* mgr)
{
    plObjInterface::write(S, mgr);

    fLocalToParent.write(S);
    fParentToLocal.write(S);
    fLocalToWorld.write(S);
    fWorldToLocal.write(S);

    S->writeInt(fChildren.size());
    for (size_t i=0; i<fChildren.size(); i++)
        mgr->writeKey(S, fChildren[i]);
}

void plCoordinateInterface::IPrcWrite(pfPrcHelper* prc)
{
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("LocalToParent");
    fLocalToParent.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("ParentToLocal");
    fParentToLocal.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LocalToWorld");
    fLocalToWorld.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLocal");
    fWorldToLocal.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Children");
    for (size_t i=0; i<fChildren.size(); i++)
        plResManager::PrcWriteKey(prc, fChildren[i]);
    prc->closeTag();
}

void plCoordinateInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "LocalToParent") {
        if (tag->hasChildren())
            fLocalToParent.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "ParentToLocal") {
        if (tag->hasChildren())
            fParentToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LocalToWorld") {
        if (tag->hasChildren())
            fLocalToWorld.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldToLocal") {
        if (tag->hasChildren())
            fWorldToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Children") {
        fChildren.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fChildren.size(); i++) {
            fChildren[i] = mgr->prcParseKeyNotify(child,
                std::bind(&_setParentCallback, this, std::placeholders::_1));
            child = child->getNextSibling();
        }
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
