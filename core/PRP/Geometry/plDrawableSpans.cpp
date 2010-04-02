#include "plDrawableSpans.h"
#include "Debug/plDebug.h"

/* plDISpanIndex */
plDISpanIndex::plDISpanIndex() : fFlags(0) { }

plDISpanIndex::plDISpanIndex(const plDISpanIndex& init)
             : fFlags(init.fFlags), fIndices(init.fIndices) { }

plDISpanIndex& plDISpanIndex::operator=(const plDISpanIndex& cpy) {
    fFlags = cpy.fFlags;
    fIndices = cpy.fIndices;
    return *this;
}


/* plDrawableSpans */
plDrawableSpans::plDrawableSpans()
               : fSpaceTree(NULL), fProps(0), fCriteria(0), fRenderLevel(0) { }

plDrawableSpans::~plDrawableSpans() {
    for (size_t i=0; i<fSourceSpans.getSize(); i++)
        delete fSourceSpans[i];
    for (size_t i=0; i<fGroups.getSize(); i++)
        delete fGroups[i];
    for (size_t i=0; i<fSpans.getSize(); i++)
        delete fSpans[i];
    if (fSpaceTree != NULL)
        delete fSpaceTree;
}

void plDrawableSpans::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fProps = S->readInt();
    fCriteria = S->readInt();
    fRenderLevel = S->readInt();

    fMaterials.setSize(S->readInt());
    for (size_t i=0; i<fMaterials.getSize(); i++)
        fMaterials[i] = mgr->readKey(S);

    for (size_t i=0; i<fSpans.getSize(); i++)
        delete fSpans[i];

    fIcicles.setSize(S->readInt());
    for (size_t i=0; i<fIcicles.getSize(); i++) {
        fIcicles[i] = new plIcicle();
        fIcicles[i]->read(S);
    }

    if (S->getVer() < pvHex) {
        if (S->readInt() != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Unsupported field count > 0");
    }

    fSpans.setSizeNull(S->readInt());
    fSpanSourceIndices.setSizeNull(fSpans.getSize());
    for (size_t i=0; i<fSpanSourceIndices.getSize(); i++) {
        fSpanSourceIndices[i] = S->readInt();
        if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeIcicle)
            fSpans[i] = fIcicles[fSpanSourceIndices[i] & kSpanIDMask];
        else if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeParticleSpan)
            fSpans[i] = fParticleSpans[fSpanSourceIndices[i] & kSpanIDMask];
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

    for (size_t i=0; i<fSourceSpans.getSize(); i++)
        delete fSourceSpans[i];
    fSourceSpans.setSizeNull(S->readInt());
    if (fSourceSpans.getSize() > 0)
        plDebug::Debug("Reading deprecated SourceSpans");
    for (size_t i=0; i<fSourceSpans.getSize(); i++) {
        fSourceSpans[i] = new plGeometrySpan();
        fSourceSpans[i]->read(S);
        if (fSpans[i]->getMaterialIdx() == 0xFFFFFFFF)
            fSourceSpans[i]->setMaterial(NULL);
        else
            fSourceSpans[i]->setMaterial(fMaterials[fSpans[i]->getMaterialIdx()]);
        fSourceSpans[i]->setFogEnvironment(fSpans[i]->getFogEnvironment());
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
        fDIIndices[i].fFlags = S->readInt();
        fDIIndices[i].fIndices.setSize(S->readInt());
        for (size_t j=0; j<(fDIIndices[i].fIndices.getSize()); j++)
            fDIIndices[i].fIndices[j] = S->readInt();
    }

    for (size_t i=0; i<fGroups.getSize(); i++)
        delete fGroups[i];
    fGroups.setSizeNull(S->readInt());
    for (size_t i=0; i<fGroups.getSize(); i++) {
        fGroups[i] = new plGBufferGroup(0);
        fGroups[i]->read(S);
    }

    setSpaceTree(plSpaceTree::Convert(mgr->ReadCreatable(S)));
    fSceneNode = mgr->readKey(S);
}

void plDrawableSpans::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(fProps);
    S->writeInt(fCriteria);
    S->writeInt(fRenderLevel);

    S->writeInt(fMaterials.getSize());
    for (size_t i=0; i<fMaterials.getSize(); i++)
        mgr->writeKey(S, fMaterials[i]);

    S->writeInt(fIcicles.getSize());
    for (size_t i=0; i<fIcicles.getSize(); i++)
        fIcicles[i]->write(S);

    S->writeInt(0); // Particle spans (unused)

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
        S->writeInt(fDIIndices[i].fFlags);
        S->writeInt(fDIIndices[i].fIndices.getSize());
        for (size_t j=0; j<fDIIndices[i].fIndices.getSize(); j++)
            S->writeInt(fDIIndices[i].fIndices[j]);
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
    prc->writeParamHex("RenderLevel", fRenderLevel);
    prc->endTag(true);

    prc->writeSimpleTag("Materials");
    for (size_t i=0; i<fMaterials.getSize(); i++)
        fMaterials[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Icicles");
    for (size_t i=0; i<fIcicles.getSize(); i++)
        fIcicles[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("ParticleSpans");
    for (size_t i=0; i<fParticleSpans.getSize(); i++)
        fParticleSpans[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SpanSourceIndices");
    for (size_t i=0; i<fSpanSourceIndices.getSize(); i++) {
        prc->startTag("SourceIndex");
        prc->writeParamHex("type", fSpanSourceIndices[i] & kSpanTypeMask);
        prc->writeParam("value", fSpanSourceIndices[i] & kSpanIDMask);
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
        prc->writeParamHex("Flags", fDIIndices[i].fFlags);
        prc->endTag();
        for (size_t j=0; j<fDIIndices[i].fIndices.getSize(); j++) {
            prc->startTag("Index");
            prc->writeParam("value", fDIIndices[i].fIndices[j]);
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
        fRenderLevel = tag->getParam("RenderLevel", "0").toUint();
    } else if (tag->getName() == "Materials") {
        fMaterials.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMaterials.getSize(); i++) {
            fMaterials[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Icicles") {
        for (size_t i=0; i<fIcicles.getSize(); i++)
            delete fIcicles[i];
        fIcicles.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fIcicles.getSize(); i++) {
            fIcicles[i] = new plIcicle();
            fIcicles[i]->prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "ParticleSpans") {
        for (size_t i=0; i<fParticleSpans.getSize(); i++)
            delete fParticleSpans[i];
        fParticleSpans.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fParticleSpans.getSize(); i++) {
            fParticleSpans[i] = new plParticleSpan();
            fParticleSpans[i]->prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SpanSourceIndices") {
        fSpans.setSizeNull(tag->countChildren());
        fSpanSourceIndices.setSizeNull(fSpans.getSize());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSpanSourceIndices.getSize(); i++) {
            if (child->getName() != "SourceIndex")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fSpanSourceIndices[i] = child->getParam("value", "0").toUint()
                                  | child->getParam("type", "0").toUint();
            if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeIcicle)
                fSpans[i] = fIcicles[fSpanSourceIndices[i] & kSpanIDMask];
            else if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeParticleSpan)
                fSpans[i] = fParticleSpans[fSpanSourceIndices[i] & kSpanIDMask];
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
        for (size_t i=0; i<fSourceSpans.getSize(); i++)
            delete fSourceSpans[i];
        fSourceSpans.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSourceSpans.getSize(); i++) {
            fSourceSpans[i] = new plGeometrySpan();
            fSourceSpans[i]->prcParse(tag);
            if (fSpans[i]->getMaterialIdx() == 0xFFFFFFFF)
                fSourceSpans[i]->setMaterial(NULL);
            else
                fSourceSpans[i]->setMaterial(fMaterials[fSpans[i]->getMaterialIdx()]);
            fSourceSpans[i]->setFogEnvironment(fSpans[i]->getFogEnvironment());
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

            fDIIndices[i].fFlags = child->getParam("Flags", "0").toUint();
            fDIIndices[i].fIndices.setSize(child->countChildren());
            const pfPrcTag* subChild = child->getFirstChild();
            for (size_t j=0; j<(fDIIndices[i].fIndices.getSize()); j++) {
                if (subChild->getName() != "Index")
                    throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                fDIIndices[i].fIndices[j] = subChild->getParam("value", "0").toUint();
                subChild = subChild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "BufferGroups") {
        for (size_t i=0; i<fGroups.getSize(); i++)
            delete fGroups[i];
        fGroups.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fGroups.getSize(); i++) {
            fGroups[i] = new plGBufferGroup(0);
            fGroups[i]->prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SpaceTree") {
        if (tag->hasChildren())
            setSpaceTree(plSpaceTree::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

void plDrawableSpans::CalcBounds() {
    for (size_t i=0; i<fIcicles.getSize(); i++) {
        if (i == 0)
            fWorldBounds = fIcicles[i]->getWorldBounds();
        else
            fWorldBounds += fIcicles[i]->getWorldBounds();
    }
    fWorldBounds.setFlags(hsBounds3Ext::kAxisAligned);
    fLocalBounds.setMins(fWorldBounds.getMins());
    fLocalBounds.setMaxs(fWorldBounds.getMaxs());
    fLocalBounds.setCorner(fWorldBounds.getCorner());
    fLocalBounds.setAxis(0, hsVector3(0.0f, fLocalBounds.getMaxs().Y - fLocalBounds.getMins().Y, 0.0f));
    fLocalBounds.setAxis(1, hsVector3(0.0f, 0.0f, fLocalBounds.getMaxs().Z - fLocalBounds.getMins().Z));
    fLocalBounds.setAxis(2, hsVector3(fLocalBounds.getMaxs().X - fLocalBounds.getMins().X, 0.0f, 0.0f));
}

void plDrawableSpans::BuildSpaceTree() {
    plSpaceTree* tree = new plSpaceTree();
    std::vector<plSpaceBuilderNode*> leaves;
    leaves.resize(fIcicles.getSize());
    for (size_t i=0; i<leaves.size(); i++) {
        leaves[i] = new plSpaceBuilderNode();
        leaves[i]->fBounds = fIcicles[i]->getWorldBounds();
        leaves[i]->fBounds.updateCenter();
    }
    plSpaceBuilderNode* root = IBuildTree(leaves);
    tree->buildTree(root);
    setSpaceTree(tree);
    delete root;
}

plSpaceBuilderNode* plDrawableSpans::IBuildTree(std::vector<plSpaceBuilderNode*>& nodes) {
    if (nodes.size() == 0)
        return NULL;
    if (nodes.size() == 1)
        return nodes[0];
    plSpaceBuilderNode* node = new plSpaceBuilderNode();
    std::vector<plSpaceBuilderNode*> left, right;
    ISplitSpace(nodes, left, right);
    plSpaceBuilderNode* lNode = IBuildTree(left);
    plSpaceBuilderNode* rNode = IBuildTree(right);
    node->fBounds = lNode->fBounds + rNode->fBounds;
    node->fBounds.setFlags(hsBounds3Ext::kAxisAligned);
    node->fBounds.updateCenter();
    node->fChildren[0] = lNode;
    node->fChildren[1] = rNode;
    return node;
}

void plDrawableSpans::ISplitSpace(std::vector<plSpaceBuilderNode*>& nodes,
                                  std::vector<plSpaceBuilderNode*>& left,
                                  std::vector<plSpaceBuilderNode*>& right) {
    hsVector3 big(0.0f, 0.0f, 0.0f);
    for (size_t i=0; i<nodes.size(); i++) {
        if (nodes[i]->fBounds.getMaxs().X - nodes[i]->fBounds.getMins().X > big.X)
            big.X = nodes[i]->fBounds.getMaxs().X - nodes[i]->fBounds.getMins().X;
        if (nodes[i]->fBounds.getMaxs().Y - nodes[i]->fBounds.getMins().Y > big.Y)
            big.Y = nodes[i]->fBounds.getMaxs().Y - nodes[i]->fBounds.getMins().Y;
        if (nodes[i]->fBounds.getMaxs().Z - nodes[i]->fBounds.getMins().Z > big.Z)
            big.Z = nodes[i]->fBounds.getMaxs().Z - nodes[i]->fBounds.getMins().Z;
    }
    if (big.X >= big.Y && big.X >= big.Z)
        ISortSpace(nodes, 0);
    else if (big.Y >= big.X && big.Y >= big.Z)
        ISortSpace(nodes, 1);
    else
        ISortSpace(nodes, 2);
    left.resize(nodes.size() / 2);
    right.resize(nodes.size() - left.size());
    std::copy(nodes.begin(), nodes.begin() + left.size(), left.begin());
    std::copy(nodes.begin() + left.size(), nodes.end(), right.begin());
}

void plDrawableSpans::ISortSpace(std::vector<plSpaceBuilderNode*>& nodes, int axis) {
    if (nodes.size() < 2)
        // Already sorted
        return;

    // Merge sort, using the bounds center along an axis for sorting >.>
    std::list<plSpaceBuilderNode*> left, right;
    plSpaceBuilderNode* pivot = nodes[0];
    for (size_t i=1; i<nodes.size(); i++) {
        switch (axis) {
        case 0:
            if (nodes[i]->fBounds.getCenter().X < pivot->fBounds.getCenter().X)
                left.push_back(nodes[i]);
            else
                right.push_back(nodes[i]);
            break;
        case 1:
            if (nodes[i]->fBounds.getCenter().Y < pivot->fBounds.getCenter().Y)
                left.push_back(nodes[i]);
            else
                right.push_back(nodes[i]);
            break;
        case 2:
            if (nodes[i]->fBounds.getCenter().Z < pivot->fBounds.getCenter().Z)
                left.push_back(nodes[i]);
            else
                right.push_back(nodes[i]);
            break;
        }
    }
    // Don't shoot me!
    std::vector<plSpaceBuilderNode*> lvec(left.begin(), left.end());
    std::vector<plSpaceBuilderNode*> rvec(right.begin(), right.end());
    ISortSpace(lvec, axis);
    ISortSpace(rvec, axis);
    std::vector<plSpaceBuilderNode*>::iterator cit = nodes.begin();
    cit = std::copy(lvec.begin(), lvec.end(), cit);
    *cit++ = pivot;
    std::copy(rvec.begin(), rvec.end(), cit);
}

void plDrawableSpans::clearSpans() {
    for (size_t i=0; i<fSpans.getSize(); i++)
        delete fSpans[i];
    fIcicles.clear();
    fParticleSpans.clear();
    fSpans.clear();
    fSpanSourceIndices.clear();
}

size_t plDrawableSpans::addIcicle(const plIcicle& span) {
    plIcicle* iceCopy = new plIcicle(span);
    fIcicles.append(iceCopy);
    size_t iceId = fIcicles.getSize() - 1;
    fSpans.append(fIcicles[iceId]);
    fSpanSourceIndices.append(iceId | kSpanTypeIcicle);
    return fSpans.getSize() - 1;
}

size_t plDrawableSpans::createBufferGroup(unsigned char format) {
    fGroups.append(new plGBufferGroup(format));
    return fGroups.getSize() - 1;
}

void plDrawableSpans::deleteBufferGroup(size_t group) {
    delete fGroups[group];
    fGroups.remove(group);
}

hsTArray<plGBufferVertex> plDrawableSpans::getVerts(const plIcicle* span) const {
    return fGroups[span->getGroupIdx()]->getVertices(span->getVBufferIdx(),
                span->getVStartIdx(), span->getVLength());
}

hsTArray<unsigned short> plDrawableSpans::getIndices(const plIcicle* span) const {
    return fGroups[span->getGroupIdx()]->getIndices(span->getIBufferIdx(),
                span->getIStartIdx(), span->getILength(), span->getVStartIdx());
}

hsTArray<plGBufferCell> plDrawableSpans::getCells(size_t group, size_t buffer) const {
    return fGroups[group]->getCells(buffer);
}

void plDrawableSpans::addVerts(size_t group, const hsTArray<plGBufferVertex>& verts) {
    fGroups[group]->addVertices(verts);
}

void plDrawableSpans::addIndices(size_t group, const hsTArray<unsigned short>& indices) {
    fGroups[group]->addIndices(indices);
}

void plDrawableSpans::addCells(size_t group, const hsTArray<plGBufferCell>& cells) {
    fGroups[group]->addCells(cells);
}

void plDrawableSpans::clearTransforms() {
    fLocalToWorlds.clear();
    fWorldToLocals.clear();
    fLocalToBones.clear();
    fBoneToLocals.clear();
}

void plDrawableSpans::addTransform(const hsMatrix44& l2w, const hsMatrix44& w2l,
                                   const hsMatrix44& l2b, const hsMatrix44& b2l) {
    fLocalToWorlds.append(l2w);
    fWorldToLocals.append(w2l);
    fLocalToBones.append(l2b);
    fBoneToLocals.append(b2l);
}

void plDrawableSpans::setSpaceTree(plSpaceTree* tree) {
    if (fSpaceTree != NULL)
        delete fSpaceTree;
    fSpaceTree = tree;
}
