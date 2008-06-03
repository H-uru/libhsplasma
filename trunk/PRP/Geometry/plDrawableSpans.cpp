#include "plDrawableSpans.h"

/* plDrawable */
plDrawable::plDrawable() { }
plDrawable::~plDrawable() { }

IMPLEMENT_CREATABLE(plDrawable, kDrawable, hsKeyedObject)


/* plDrawableSpans */
plDrawableSpans::plDrawableSpans()
               : fSpaceTree(NULL), fProps(0), fCriteria(0) { }

plDrawableSpans::~plDrawableSpans() {
    for (size_t i=0; i<fSourceSpans.getSize(); i++)
        delete fSourceSpans[i];
    for (size_t i=0; i<fDIIndices.getSize(); i++)
        delete fDIIndices[i];
    for (size_t i=0; i<fGroups.getSize(); i++)
        delete fGroups[i];
    if (fSpaceTree != NULL)
        delete fSpaceTree;
}

IMPLEMENT_CREATABLE(plDrawableSpans, kDrawableSpans, plDrawable)

void plDrawableSpans::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fProps = S->readInt();
    fCriteria = S->readInt();
    fRenderLevel.level = S->readInt();

    fMaterials.setSize(S->readInt());
    for (size_t i=0; i<fMaterials.getSize(); i++)
        fMaterials[i] = mgr->readKey(S);

    fIcicles.setSize(S->readInt());
    for (size_t i=0; i<fIcicles.getSize(); i++)
        fIcicles[i].read(S);
    S->readInt(); // Discarded -- Icicles2

    fSpans.setSizeNull(S->readInt());
    fSpanSourceIndices.setSizeNull(fSpans.getSize());
    for (size_t i=0; i<fSpanSourceIndices.getSize(); i++) {
        fSpanSourceIndices[i] = S->readInt();
        if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeIcicle)
            fSpans[i] = &(fIcicles[fSpanSourceIndices[i] & kSpanIDMask]);
        else if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeParticleSpan)
            fSpans[i] = &(fParticleSpans[fSpanSourceIndices[i] & kSpanIDMask]);
        //if (fSpans[fSpans.getSize()-1]->getTypeMask() & plSpan::kParticleSpan) {
        //    plParticleSpan* ps = (plParticleSpan*)fSpans[fSpans.getSize()-1];
        //    ps->setSrcSpanIdx(fSpans.getSize()-1);
        //}
    }

    for (size_t i=0; i<fSpans.getSize(); i++)
        fSpans[i]->setFogEnvironment(mgr->readKey(S));

    if (fSpans.getSize() > 0) {
        fLocalBounds.read(S);
        fWorldBounds.read(S);
        fMaxWorldBounds.read(S);
    } else {
        fLocalBounds.setType(hsBounds3::kIsSphere);
        fWorldBounds.setType(hsBounds3::kIsSphere);
        fMaxWorldBounds.setType(hsBounds3::kIsSphere);
    }

    for (size_t i=0; i<fSpans.getSize(); i++) {
        if (fSpans[i]->getProps() & plSpan::kPropHasPermaLights) {
            size_t count = S->readInt();
            for (size_t j=0; j<count; j++)
                fSpans[i]->addPermaLight(mgr->readKey(S));
        }
        if (fSpans[i]->getProps() & plSpan::kPropHasPermaProjs) {
            size_t count = S->readInt();
            for (size_t j=0; j<count; j++)
                fSpans[i]->addPermaProj(mgr->readKey(S));
        }
    }

    fSourceSpans.setSize(S->readInt());
    for (size_t i=0; i<fSourceSpans.getSize(); i++) {
        fSourceSpans[i] = new plGeometrySpan();
        fSourceSpans[i]->read(S);
        if (fSpans[i]->getMaterialIdx() == 0xFFFFFFFF)
            fSourceSpans[i]->setMaterial(NULL);
        else
            fSourceSpans[i]->setMaterial(fMaterials[fSpans[i]->getMaterialIdx()]);
        fSourceSpans[i]->setFogEnvironment(fSpans[i]->getFogEnvironment());
        //fSourceSpans[i]->setSpanRefIndex(i);
    }

    size_t xformCount = S->readInt();
    fLocalToWorlds.setSize(xformCount);
    fWorldToLocals.setSize(xformCount);
    fLocalToBones.setSize(xformCount);
    fBoneToLocals.setSize(xformCount);
    for (size_t i=0; i<xformCount; i++) {
        fLocalToWorlds[i].read(S);
        fWorldToLocals[i].read(S);
        fLocalToBones[i].read(S);
        fBoneToLocals[i].read(S);
    }

    fDIIndices.setSize(S->readInt());
    for (size_t i=0; i<fDIIndices.getSize(); i++) {
        fDIIndices[i] = new plDISpanIndex();
        fDIIndices[i]->fFlags = S->readInt();

        fDIIndices[i]->fIndices.setSize(S->readInt());
        for (size_t j=0; j<(fDIIndices[i]->fIndices.getSize()); j++)
            fDIIndices[i]->fIndices[j] = S->readInt();
    }

    fGroups.setSize(S->readInt());
    for (size_t i=0; i<fGroups.getSize(); i++) {
        fGroups[i] = new plGBufferGroup(0, fProps & kPropVolatile, fProps & kPropSortFaces, 0);
        fGroups[i]->read(S);
    }

    /*
    if (fProps & kPropSortFaces) {
        for (i=0; i<fSpans.getSize(); i++)
            IMakeSpanSortable(i);
    }
    */

    fSpaceTree = plSpaceTree::Convert(mgr->ReadCreatable(S));
    fSceneNode = mgr->readKey(S);

    /*
    if (GetNativeProperty(kPropCharacter)) {
        visSet[1] = true;
        for (int i=0; i<fSpans.getCount(); i++)
            fSpans[i]->visSet[1] = true;
    }*/
}

void plDrawableSpans::write(hsStream* S, plResManager* mgr) {
    //if (needCleanup)
    //    IRemoveGarbage();
    hsKeyedObject::write(S, mgr);

    S->writeInt(fProps);
    S->writeInt(fCriteria);
    S->writeInt(fRenderLevel.level);

    S->writeInt(fMaterials.getSize());
    for (size_t i=0; i<fMaterials.getSize(); i++)
        mgr->writeKey(S, fMaterials[i]);

    S->writeInt(fIcicles.getSize());
    for (size_t i=0; i<fIcicles.getSize(); i++)
        fIcicles[i].write(S);

    S->writeInt(0);  // No Icicles2

    S->writeInt(fSpanSourceIndices.getSize());
    for (size_t i=0; i<fSpanSourceIndices.getSize(); i++)
        S->writeInt(fSpanSourceIndices[i]);

    for (size_t i=0; i<fSpans.getSize(); i++)
        mgr->writeKey(S, fSpans[i]->getFogEnvironment());

    if (fSpans.getSize() > 0) {
        fLocalBounds.write(S);
        fWorldBounds.write(S);
        fMaxWorldBounds.write(S);
    }

    for (size_t i=0; i<fSpans.getSize(); i++) {
        if (fSpans[i]->getProps() & plSpan::kPropHasPermaLights) {
            S->writeInt(fSpans[i]->getPermaLights().getSize());
            for (size_t j=0; j<fSpans[i]->getPermaLights().getSize(); j++)
                mgr->writeKey(S, fSpans[i]->getPermaLights()[j]);
        }
        if (fSpans[i]->getProps() & plSpan::kPropHasPermaProjs) {
            S->writeInt(fSpans[i]->getPermaProjs().getSize());
            for (size_t j=0; j<fSpans[i]->getPermaProjs().getSize(); j++)
                mgr->writeKey(S, fSpans[i]->getPermaProjs()[j]);
        }
    }

    S->writeInt(fSourceSpans.getSize());
    for (size_t i=0; i<fSourceSpans.getSize(); i++)
        fSourceSpans[i]->write(S);

    S->writeInt(fLocalToWorlds.getSize());
    for (size_t i=0; i<fLocalToWorlds.getSize(); i++) {
        fLocalToWorlds[i].write(S);
        fWorldToLocals[i].write(S);
        fLocalToBones[i].write(S);
        fBoneToLocals[i].write(S);
    }

    S->writeInt(fDIIndices.getSize());
    for (size_t i=0; i<fDIIndices.getSize(); i++) {
        S->writeInt(fDIIndices[i]->fFlags);
        S->writeInt(fDIIndices[i]->fIndices.getSize());
        for (size_t j=0; j<fDIIndices[i]->fIndices.getSize(); j++)
            S->writeInt(fDIIndices[i]->fIndices[j]);
    }

    S->writeInt(fGroups.getSize());
    for (size_t i=0; i<fGroups.getSize(); i++)
        fGroups[i]->write(S);

    mgr->WriteCreatable(S, fSpaceTree);
    mgr->writeKey(S, fSceneNode);
}

void plDrawableSpans::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("Properties");
    prc->writeParamHex("Flags", fProps);
    prc->writeParamHex("Criteria", fCriteria);
    prc->writeParamHex("RenderLevel", fRenderLevel.level);
    prc->endTag(true);

    prc->writeSimpleTag("Materials");
    for (size_t i=0; i<fMaterials.getSize(); i++)
        fMaterials[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Icicles");
    for (size_t i=0; i<fIcicles.getSize(); i++)
        fIcicles[i].prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SpanSourceIndices");
    for (size_t i=0; i<fSpanSourceIndices.getSize(); i++) {
        prc->startTag("SourceIndex");
        prc->writeParam("value", fSpanSourceIndices[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("FogEnvironments");
    for (size_t i=0; i<fSpans.getSize(); i++)
        fSpans[i]->getFogEnvironment()->prcWrite(prc);
    prc->closeTag();

    if (fSpans.getSize() > 0) {
        prc->writeSimpleTag("LocalBounds");
        fLocalBounds.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("WorldBounds");
        fWorldBounds.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("MaxWorldBounds");
        fMaxWorldBounds.prcWrite(prc);
        prc->closeTag();
    }

    prc->writeSimpleTag("PermaLightInfo");
    for (size_t i=0; i<fSpans.getSize(); i++) {
        prc->writeSimpleTag("Span");
        if (fSpans[i]->getProps() & plSpan::kPropHasPermaLights) {
            prc->writeSimpleTag("PermaLights");
            for (size_t j=0; j<fSpans[i]->getPermaLights().getSize(); j++)
                fSpans[i]->getPermaLights()[j]->prcWrite(prc);
            prc->closeTag();
        }
        if (fSpans[i]->getProps() & plSpan::kPropHasPermaProjs) {
            prc->writeSimpleTag("PermaProjs");
            for (size_t j=0; j<fSpans[i]->getPermaProjs().getSize(); j++)
                fSpans[i]->getPermaProjs()[j]->prcWrite(prc);
            prc->closeTag();
        }
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("SourceSpans");
    for (size_t i=0; i<fSourceSpans.getSize(); i++)
        fSourceSpans[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Transforms");
    for (size_t i=0; i<fLocalToWorlds.getSize(); i++) {
        prc->writeSimpleTag("TransformSet");
          prc->writeSimpleTag("LocalToWorld");
          fLocalToWorlds[i].prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("WorldToLocal");
          fWorldToLocals[i].prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("LocalToBone");
          fLocalToBones[i].prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("BoneToLocal");
          fBoneToLocals[i].prcWrite(prc);
          prc->closeTag();
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("DIIndices");
    for (size_t i=0; i<fDIIndices.getSize(); i++) {
        prc->startTag("plDISpanIndex");
        prc->writeParamHex("Flags", fDIIndices[i]->fFlags);
        prc->endTag();
        for (size_t j=0; j<fDIIndices[i]->fIndices.getSize(); j++) {
            prc->startTag("Index");
            prc->writeParam("value", fDIIndices[i]->fIndices[j]);
            prc->endTag(true);
        }
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("BufferGroups");
    for (size_t i=0; i<fGroups.getSize(); i++)
        fGroups[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SpaceTree");
    if (fSpaceTree != NULL)
        fSpaceTree->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SceneNode");
    fSceneNode->prcWrite(prc);
    prc->closeTag();
}

void plDrawableSpans::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Properties") {
        fProps = tag->getParam("Flags", "0").toUint();
        fCriteria = tag->getParam("Criteria", "0").toUint();
        fRenderLevel.level = tag->getParam("RenderLevel", "0").toUint();
    } else if (tag->getName() == "Materials") {
        fMaterials.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMaterials.getSize(); i++) {
            fMaterials[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Icicles") {
        fIcicles.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fIcicles.getSize(); i++) {
            fIcicles[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SpanSourceIndices") {
        fSpans.setSizeNull(tag->countChildren());
        fSpanSourceIndices.setSizeNull(fSpans.getSize());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSpanSourceIndices.getSize(); i++) {
            if (child->getName() != "SourceIndex")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fSpanSourceIndices[i] = child->getParam("value", "0").toUint();
            if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeIcicle)
                fSpans[i] = &(fIcicles[fSpanSourceIndices[i] & kSpanIDMask]);
            else if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeParticleSpan)
                fSpans[i] = &(fParticleSpans[fSpanSourceIndices[i] & kSpanIDMask]);
            //if (fSpans[fSpans.getSize()-1]->getTypeMask() & plSpan::kParticleSpan) {
            //    plParticleSpan* ps = (plParticleSpan*)fSpans[fSpans.getSize()-1];
            //    ps->setSrcSpanIdx(fSpans.getSize()-1);
            //}
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "FogEnvironments") {
        size_t nChildren = tag->countChildren();
        if (nChildren != fSpans.getSize())
            throw pfPrcParseException(__FILE__, __LINE__, "Span count mismatch");

        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<nChildren; i++) {
            fSpans[i]->setFogEnvironment(mgr->prcParseKey(child));
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "LocalBounds") {
        if (tag->hasChildren())
            fLocalBounds.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldBounds") {
        if (tag->hasChildren())
            fWorldBounds.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "MaxWorldBounds") {
        if (tag->hasChildren())
            fMaxWorldBounds.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "PermaLightInfo") {
        size_t nChildren = tag->countChildren();
        if (nChildren != fSpans.getSize())
            throw pfPrcParseException(__FILE__, __LINE__, "Span count mismatch");

        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<nChildren; i++) {
            if (child->getName() != "Span")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            const pfPrcTag* subChild = child->getFirstChild();
            while (subChild != NULL) {
                if (subChild->getName() == "PermaLights") {
                    size_t nLights = subChild->countChildren();
                    const pfPrcTag* light = subChild->getFirstChild();
                    for (size_t j=0; j<nLights; j++) {
                        fSpans[i]->addPermaLight(mgr->prcParseKey(light));
                        light = light->getNextSibling();
                    }
                } else if (subChild->getName() == "PermaProjs") {
                    size_t nLights = subChild->countChildren();
                    const pfPrcTag* light = subChild->getFirstChild();
                    for (size_t j=0; j<nLights; j++) {
                        fSpans[i]->addPermaProj(mgr->prcParseKey(light));
                        light = light->getNextSibling();
                    }
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                }
                subChild = subChild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SourceSpans") {
        fSourceSpans.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSourceSpans.getSize(); i++) {
            fSourceSpans[i] = new plGeometrySpan();
            fSourceSpans[i]->prcParse(tag);
            if (fSpans[i]->getMaterialIdx() == 0xFFFFFFFF)
                fSourceSpans[i]->setMaterial(NULL);
            else
                fSourceSpans[i]->setMaterial(fMaterials[fSpans[i]->getMaterialIdx()]);
            fSourceSpans[i]->setFogEnvironment(fSpans[i]->getFogEnvironment());
            //fSourceSpans[i]->setSpanRefIndex(i);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Transforms") {
        fLocalToWorlds.setSize(tag->countChildren());
        fWorldToLocals.setSize(fLocalToWorlds.getSize());
        fLocalToBones.setSize(fLocalToWorlds.getSize());
        fBoneToLocals.setSize(fLocalToWorlds.getSize());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLocalToWorlds.getSize(); i++) {
            if (child->getName() != "TransformSet")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            const pfPrcTag* subChild = child->getFirstChild();
            while (subChild != NULL) {
                if (subChild->getName() == "LocalToWorld") {
                    if (subChild->hasChildren())
                        fLocalToWorlds[i].prcParse(subChild->getFirstChild());
                } else if (subChild->getName() == "WorldToLocal") {
                    if (subChild->hasChildren())
                        fWorldToLocals[i].prcParse(subChild->getFirstChild());
                } else if (subChild->getName() == "LocalToBone") {
                    if (subChild->hasChildren())
                        fLocalToBones[i].prcParse(subChild->getFirstChild());
                } else if (subChild->getName() == "BoneToLocal") {
                    if (subChild->hasChildren())
                        fBoneToLocals[i].prcParse(subChild->getFirstChild());
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                }
                subChild = subChild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "DIIndices") {
        fDIIndices.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fDIIndices.getSize(); i++) {
            if (child->getName() != "plDISpanIndex")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fDIIndices[i] = new plDISpanIndex();
            fDIIndices[i]->fFlags = child->getParam("Flags", "0").toUint();

            fDIIndices[i]->fIndices.setSize(child->countChildren());
            const pfPrcTag* subChild = child->getFirstChild();
            for (size_t j=0; j<(fDIIndices[i]->fIndices.getSize()); j++) {
                if (subChild->getName() != "Index")
                    throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                fDIIndices[i]->fIndices[j] = subChild->getParam("value", "0").toUint();
                subChild = subChild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "BufferGroups") {
        fGroups.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fGroups.getSize(); i++) {
            fGroups[i] = new plGBufferGroup(0, fProps & kPropVolatile, fProps & kPropSortFaces, 0);
            fGroups[i]->prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SpaceTree") {
        if (tag->hasChildren())
            fSpaceTree = plSpaceTree::Convert(mgr->prcParseCreatable(tag->getFirstChild()));
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
