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

#include "plDrawableSpans.h"
#include "Debug/plDebug.h"
#include "Util/hsRadixSort.h"
#include <algorithm>

/* plDISpanIndex */
plDISpanIndex& plDISpanIndex::operator=(const plDISpanIndex& cpy) {
    fFlags = cpy.fFlags;
    fIndices = cpy.fIndices;
    return *this;
}


/* plDrawableSpans */
plDrawableSpans::~plDrawableSpans() {
    for (auto group = fGroups.begin(); group != fGroups.end(); ++group)
        delete *group;
    for (auto span = fSpans.begin(); span != fSpans.end(); ++span)
        delete *span;
    delete fSpaceTree;
}

void plDrawableSpans::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fProps = S->readInt();
    fCriteria = S->readInt();
    fRenderLevel = S->readInt();

    fMaterials.resize(S->readInt());
    for (size_t i=0; i<fMaterials.size(); i++)
        fMaterials[i] = mgr->readKey(S);

    for (size_t i=0; i<fSpans.size(); i++)
        delete fSpans[i];

    fIcicles.resize(S->readInt());
    for (size_t i=0; i<fIcicles.size(); i++) {
        fIcicles[i] = new plIcicle();
        fIcicles[i]->read(S);
    }

    if (!S->getVer().isHexIsle()) {
        if (S->readInt() != 0)
            throw hsBadParamException(__FILE__, __LINE__, "Unsupported field count > 0");
    }

    fSpans.resize(S->readInt());
    fSpanSourceIndices.resize(fSpans.size());
    for (size_t i=0; i<fSpanSourceIndices.size(); i++) {
        fSpanSourceIndices[i] = S->readInt();
        if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeIcicle)
            fSpans[i] = fIcicles[fSpanSourceIndices[i] & kSpanIDMask];
        else if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeParticleSpan)
            fSpans[i] = fParticleSpans[fSpanSourceIndices[i] & kSpanIDMask];
    }

    for (size_t i=0; i<fSpans.size(); i++)
        fSpans[i]->setFogEnvironment(mgr->readKey(S));

    if (fSpans.size() > 0) {
        fLocalBounds.read(S);
        fWorldBounds.read(S);
        fMaxWorldBounds.read(S);
    } else {
        fLocalBounds.setType(hsBounds3::kIsSphere);
        fWorldBounds.setType(hsBounds3::kIsSphere);
        fMaxWorldBounds.setType(hsBounds3::kIsSphere);
    }

    for (size_t i=0; i<fSpans.size(); i++) {
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

    fSourceSpans.resize(S->readInt());
    if (fSourceSpans.size() > 0 && !S->getVer().isUniversal())
        plDebug::Debug("Reading deprecated SourceSpans");
    for (size_t i=0; i<fSourceSpans.size(); i++) {
        fSourceSpans[i] = new plGeometrySpan();
        fSourceSpans[i]->read(S);
        if (fSpans[i]->getMaterialIdx() == 0xFFFFFFFF)
            fSourceSpans[i]->setMaterial(NULL);
        else
            fSourceSpans[i]->setMaterial(fMaterials[fSpans[i]->getMaterialIdx()]);
        fSourceSpans[i]->setFogEnvironment(fSpans[i]->getFogEnvironment());
    }

    size_t xformCount = S->readInt();
    fLocalToWorlds.resize(xformCount);
    fWorldToLocals.resize(xformCount);
    fLocalToBones.resize(xformCount);
    fBoneToLocals.resize(xformCount);
    for (size_t i=0; i<xformCount; i++) {
        fLocalToWorlds[i].read(S);
        fWorldToLocals[i].read(S);
        fLocalToBones[i].read(S);
        fBoneToLocals[i].read(S);
    }

    fDIIndices.resize(S->readInt());
    for (size_t i=0; i<fDIIndices.size(); i++) {
        fDIIndices[i].fFlags = S->readInt();
        fDIIndices[i].fIndices.resize(S->readInt());
        for (size_t j=0; j<(fDIIndices[i].fIndices.size()); j++)
            fDIIndices[i].fIndices[j] = S->readInt();
    }

    for (size_t i=0; i<fGroups.size(); i++)
        delete fGroups[i];
    fGroups.resize(S->readInt());
    for (size_t i=0; i<fGroups.size(); i++) {
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

    S->writeInt(fMaterials.size());
    for (size_t i=0; i<fMaterials.size(); i++)
        mgr->writeKey(S, fMaterials[i]);

    S->writeInt(fIcicles.size());
    for (size_t i=0; i<fIcicles.size(); i++)
        fIcicles[i]->write(S);

    S->writeInt(0); // Particle spans (unused)

    S->writeInt(fSpanSourceIndices.size());
    for (size_t i=0; i<fSpanSourceIndices.size(); i++)
        S->writeInt(fSpanSourceIndices[i]);

    for (size_t i=0; i<fSpans.size(); i++)
        mgr->writeKey(S, fSpans[i]->getFogEnvironment());

    if (fSpans.size() > 0) {
        fLocalBounds.write(S);
        fWorldBounds.write(S);
        fMaxWorldBounds.write(S);
    }

    for (size_t i=0; i<fSpans.size(); i++) {
        if (fSpans[i]->getProps() & plSpan::kPropHasPermaLights) {
            S->writeInt(fSpans[i]->getPermaLights().size());
            for (size_t j=0; j<fSpans[i]->getPermaLights().size(); j++)
                mgr->writeKey(S, fSpans[i]->getPermaLights()[j]);
        }
        if (fSpans[i]->getProps() & plSpan::kPropHasPermaProjs) {
            S->writeInt(fSpans[i]->getPermaProjs().size());
            for (size_t j=0; j<fSpans[i]->getPermaProjs().size(); j++)
                mgr->writeKey(S, fSpans[i]->getPermaProjs()[j]);
        }
    }

    S->writeInt(fSourceSpans.size());
    for (size_t i=0; i<fSourceSpans.size(); i++)
        fSourceSpans[i]->write(S);

    S->writeInt(fLocalToWorlds.size());
    for (size_t i=0; i<fLocalToWorlds.size(); i++) {
        fLocalToWorlds[i].write(S);
        fWorldToLocals[i].write(S);
        fLocalToBones[i].write(S);
        fBoneToLocals[i].write(S);
    }

    S->writeInt(fDIIndices.size());
    for (size_t i=0; i<fDIIndices.size(); i++) {
        S->writeInt(fDIIndices[i].fFlags);
        S->writeInt(fDIIndices[i].fIndices.size());
        for (size_t j=0; j<fDIIndices[i].fIndices.size(); j++)
            S->writeInt(fDIIndices[i].fIndices[j]);
    }

    S->writeInt(fGroups.size());
    for (size_t i=0; i<fGroups.size(); i++)
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
    for (size_t i=0; i<fMaterials.size(); i++)
        plResManager::PrcWriteKey(prc, fMaterials[i]);
    prc->closeTag();

    prc->writeSimpleTag("Icicles");
    for (size_t i=0; i<fIcicles.size(); i++)
        fIcicles[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("ParticleSpans");
    for (size_t i=0; i<fParticleSpans.size(); i++)
        fParticleSpans[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SpanSourceIndices");
    for (size_t i=0; i<fSpanSourceIndices.size(); i++) {
        prc->startTag("SourceIndex");
        prc->writeParamHex("type", fSpanSourceIndices[i] & kSpanTypeMask);
        prc->writeParam("value", fSpanSourceIndices[i] & kSpanIDMask);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("FogEnvironments");
    for (size_t i=0; i<fSpans.size(); i++)
        plResManager::PrcWriteKey(prc, fSpans[i]->getFogEnvironment());
    prc->closeTag();

    if (fSpans.size() > 0) {
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
    for (size_t i=0; i<fSpans.size(); i++) {
        prc->writeSimpleTag("Span");
        if (fSpans[i]->getProps() & plSpan::kPropHasPermaLights) {
            prc->writeSimpleTag("PermaLights");
            for (size_t j=0; j<fSpans[i]->getPermaLights().size(); j++)
                plResManager::PrcWriteKey(prc, fSpans[i]->getPermaLights()[j]);
            prc->closeTag();
        }
        if (fSpans[i]->getProps() & plSpan::kPropHasPermaProjs) {
            prc->writeSimpleTag("PermaProjs");
            for (size_t j=0; j<fSpans[i]->getPermaProjs().size(); j++)
                plResManager::PrcWriteKey(prc, fSpans[i]->getPermaProjs()[j]);
            prc->closeTag();
        }
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("SourceSpans");
    for (size_t i=0; i<fSourceSpans.size(); i++)
        fSourceSpans[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Transforms");
    for (size_t i=0; i<fLocalToWorlds.size(); i++) {
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
    for (size_t i=0; i<fDIIndices.size(); i++) {
        prc->startTag("plDISpanIndex");
        prc->writeParamHex("Flags", fDIIndices[i].fFlags);
        prc->endTag();
        for (size_t j=0; j<fDIIndices[i].fIndices.size(); j++) {
            prc->startTag("Index");
            prc->writeParam("value", fDIIndices[i].fIndices[j]);
            prc->endTag(true);
        }
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("BufferGroups");
    for (size_t i=0; i<fGroups.size(); i++)
        fGroups[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SpaceTree");
    if (fSpaceTree != NULL)
        fSpaceTree->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SceneNode");
    plResManager::PrcWriteKey(prc, fSceneNode);
    prc->closeTag();
}

void plDrawableSpans::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Properties") {
        fProps = tag->getParam("Flags", "0").to_uint();
        fCriteria = tag->getParam("Criteria", "0").to_uint();
        fRenderLevel = tag->getParam("RenderLevel", "0").to_uint();
    } else if (tag->getName() == "Materials") {
        fMaterials.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMaterials.size(); i++) {
            fMaterials[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Icicles") {
        for (size_t i=0; i<fIcicles.size(); i++)
            delete fIcicles[i];
        fIcicles.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fIcicles.size(); i++) {
            fIcicles[i] = new plIcicle();
            fIcicles[i]->prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "ParticleSpans") {
        for (size_t i=0; i<fParticleSpans.size(); i++)
            delete fParticleSpans[i];
        fParticleSpans.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fParticleSpans.size(); i++) {
            fParticleSpans[i] = new plParticleSpan();
            fParticleSpans[i]->prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SpanSourceIndices") {
        fSpans.resize(tag->countChildren());
        fSpanSourceIndices.resize(fSpans.size());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSpanSourceIndices.size(); i++) {
            if (child->getName() != "SourceIndex")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fSpanSourceIndices[i] = child->getParam("value", "0").to_uint()
                                  | child->getParam("type", "0").to_uint();
            if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeIcicle)
                fSpans[i] = fIcicles[fSpanSourceIndices[i] & kSpanIDMask];
            else if ((fSpanSourceIndices[i] & kSpanTypeMask) == kSpanTypeParticleSpan)
                fSpans[i] = fParticleSpans[fSpanSourceIndices[i] & kSpanIDMask];
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "FogEnvironments") {
        size_t nChildren = tag->countChildren();
        if (nChildren != fSpans.size())
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
        if (nChildren != fSpans.size())
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
        fSourceSpans.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSourceSpans.size(); i++) {
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
        fLocalToWorlds.resize(tag->countChildren());
        fWorldToLocals.resize(fLocalToWorlds.size());
        fLocalToBones.resize(fLocalToWorlds.size());
        fBoneToLocals.resize(fLocalToWorlds.size());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLocalToWorlds.size(); i++) {
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
        fDIIndices.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fDIIndices.size(); i++) {
            if (child->getName() != "plDISpanIndex")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());

            fDIIndices[i].fFlags = child->getParam("Flags", "0").to_uint();
            fDIIndices[i].fIndices.resize(child->countChildren());
            const pfPrcTag* subChild = child->getFirstChild();
            for (size_t j=0; j<(fDIIndices[i].fIndices.size()); j++) {
                if (subChild->getName() != "Index")
                    throw pfPrcTagException(__FILE__, __LINE__, subChild->getName());
                fDIIndices[i].fIndices[j] = subChild->getParam("value", "0").to_uint();
                subChild = subChild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "BufferGroups") {
        for (size_t i=0; i<fGroups.size(); i++)
            delete fGroups[i];
        fGroups.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fGroups.size(); i++) {
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

void plDrawableSpans::calcBounds() {
    for (size_t i=0; i<fIcicles.size(); i++) {
        std::vector<plGBufferVertex> verts = getVerts(fIcicles[i]);
        hsBounds3Ext loc;
        hsBounds3Ext world;

        world.setFlags(hsBounds3Ext::kAxisAligned);
        for (size_t j = 0; j < verts.size(); j++) {
            loc += verts[j].fPos;
            world += fIcicles[i]->getLocalToWorld().multPoint(verts[j].fPos);
        }
        loc.unalign();

        fIcicles[i]->setLocalBounds(loc);
        fIcicles[i]->setWorldBounds(world);

        if (i == 0)
            fWorldBounds = world;
        else
            fWorldBounds += world;
    }

    fWorldBounds.setFlags(hsBounds3Ext::kAxisAligned);

    fLocalBounds.setMins(fWorldBounds.getMins());
    fLocalBounds.setMaxs(fWorldBounds.getMaxs());
    fLocalBounds.unalign();
}

void plDrawableSpans::BuildSpaceTree() {
    plSpaceTree* tree = new plSpaceTree();
    std::vector<plSpaceBuilderNode*> leaves;
    leaves.resize(fIcicles.size());
    for (size_t i=0; i<leaves.size(); i++) {
        leaves[i] = new plSpaceBuilderNode();
        leaves[i]->fBounds = fIcicles[i]->getWorldBounds();
        leaves[i]->fBounds.updateCenter();
        leaves[i]->fDataIndex = i;
    }
    plSpaceBuilderNode* root = IBuildTree(leaves);
    tree->buildTree(root, leaves.size());
    setSpaceTree(tree);
    delete root;
}

plSpaceBuilderNode* plDrawableSpans::IBuildTree(std::vector<plSpaceBuilderNode*>& nodes) {
    if (nodes.empty())
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

    hsRadixSort rad;
    hsRadixSortElem* list = new hsRadixSortElem[nodes.size()];
    hsRadixSortElem* it = list;
    for (int i = nodes.size() - 1; i >= 0; i--) {
        switch (axis) {
        case 0:
            it->fKey.fFloat = nodes[i]->fBounds.getCenter().X;
            break;
        case 1:
            it->fKey.fFloat = nodes[i]->fBounds.getCenter().Y;
            break;
        case 2:
            it->fKey.fFloat = nodes[i]->fBounds.getCenter().Z;
            break;
        }

        it->fData = nodes[i];
        it->fNext = it + 1;
        it++;
    }
    list[nodes.size() - 1].fNext = NULL;

    it = rad.sort(list, hsRadixSort::kFloat);

    for (size_t i = 0; i < nodes.size(); i++) {
        nodes[i] = (plSpaceBuilderNode*)it->fData;
        it = it->fNext;
    }

    delete[] list;
}

void plDrawableSpans::clearSpans() {
    for (auto span = fSpans.begin(); span != fSpans.end(); ++span)
        delete *span;
    fIcicles.clear();
    fParticleSpans.clear();
    fSpans.clear();
    fSpanSourceIndices.clear();
}

size_t plDrawableSpans::addIcicle(const plIcicle& span) {
    plIcicle* iceCopy = new plIcicle(span);
    fIcicles.push_back(iceCopy);
    size_t iceId = fIcicles.size() - 1;
    fSpans.push_back(fIcicles[iceId]);
    fSpanSourceIndices.push_back(iceId | kSpanTypeIcicle);
    return fSpans.size() - 1;
}

size_t plDrawableSpans::createBufferGroup(unsigned char format) {
    fGroups.push_back(new plGBufferGroup(format));
    return fGroups.size() - 1;
}

void plDrawableSpans::deleteBufferGroup(size_t group) {
    delete fGroups[group];
    fGroups.erase(fGroups.begin() + group);
}

std::vector<plGBufferVertex> plDrawableSpans::getVerts(const plIcicle* span) const {
    return fGroups[span->getGroupIdx()]->getVertices(span->getVBufferIdx(),
                span->getVStartIdx(), span->getVLength());
}

std::vector<unsigned short> plDrawableSpans::getIndices(const plIcicle* span) const {
    return fGroups[span->getGroupIdx()]->getIndices(span->getIBufferIdx(),
                span->getIStartIdx(), span->getILength(), span->getVStartIdx());
}

std::vector<plGBufferCell> plDrawableSpans::getCells(size_t group, size_t buffer) const {
    return fGroups[group]->getCells(buffer);
}

void plDrawableSpans::addVerts(size_t group, const std::vector<plGBufferVertex>& verts) {
    fGroups[group]->addVertices(verts);
}

void plDrawableSpans::addIndices(size_t group, const std::vector<unsigned short>& indices) {
    fGroups[group]->addIndices(indices);
}

void plDrawableSpans::addCells(size_t group, const std::vector<plGBufferCell>& cells) {
    fGroups[group]->addCells(cells);
}

size_t plDrawableSpans::addDIIndex(const plDISpanIndex& idx) {
    fDIIndices.push_back(idx);
    return fDIIndices.size() - 1;
}

void plDrawableSpans::clearTransforms() {
    fLocalToWorlds.clear();
    fWorldToLocals.clear();
    fLocalToBones.clear();
    fBoneToLocals.clear();
}

void plDrawableSpans::addTransform(const hsMatrix44& l2w, const hsMatrix44& w2l,
                                   const hsMatrix44& l2b, const hsMatrix44& b2l) {
    fLocalToWorlds.push_back(l2w);
    fWorldToLocals.push_back(w2l);
    fLocalToBones.push_back(l2b);
    fBoneToLocals.push_back(b2l);
}

void plDrawableSpans::setSpaceTree(plSpaceTree* tree) {
    delete fSpaceTree;
    fSpaceTree = tree;
}

void plDrawableSpans::composeGeometry(bool clearspans, bool calcbounds) {
    std::map<unsigned int, std::pair<plGBufferGroup*, size_t> > groups;
    for (auto group = fGroups.begin(); group != fGroups.end(); ++group)
        delete *group;
    for (auto span = fSpans.begin(); span != fSpans.end(); ++span)
        delete *span;

    for (size_t i=0; i<fSourceSpans.size(); i++) {
        plGeometrySpan* span = fSourceSpans[i];
        unsigned int format = span->getFormat();
        plGBufferGroup* group = groups[format].first;
        if (!group) {
            group = new plGBufferGroup(format);
            groups[format] = std::make_pair(group, fGroups.size());
            fGroups.push_back(group);
        }
        size_t buf_idx = group->getNumVertBuffers();
        std::vector<unsigned short> indices = span->getIndices();
        std::vector<plGeometrySpan::TempVertex> verts = span->getVertices();

        plGBufferCell cell;
        cell.fColorStart = -1;
        cell.fVtxStart = 0;
        cell.fLength = verts.size();
        std::vector<plGBufferCell> cell_tmp;
        cell_tmp.push_back(cell);

        std::vector<plGBufferVertex> new_verts;
        new_verts.resize(verts.size());
        for (size_t j=0; j<verts.size(); j++) {
            plGeometrySpan::TempVertex v1 = verts[j];
            plGBufferVertex v2;
            v2.fPos = v1.fPosition;
            v2.fNormal = v1.fNormal;
            for (size_t k=0; k<8; k++) {
                v2.fUVWs[k] = v1.fUVs[k];
            }
            for (size_t k=0; k<3; k++) {
                v2.fSkinWeights[k] = v1.fWeights[k];
            }
            v2.fSkinIdx = v1.fIndices;
            v2.fColor = v1.fColor;
            new_verts[j] = v2;
        }
        group->addIndices(indices);
        group->addVertices(new_verts);
        group->addCells(cell_tmp);

        auto mat_f = std::find(fMaterials.begin(), fMaterials.end(), span->getMaterial());
        size_t mat_idx = -1;
        if (mat_f == fMaterials.end()) {
            fMaterials.push_back(span->getMaterial());
            mat_idx = fMaterials.size() - 1;
        } else {
            mat_idx = mat_f - fMaterials.begin();
        }

        plIcicle icicle;
        icicle.setIBufferIdx(buf_idx);
        icicle.setIStartIdx(0);
        icicle.setILength(indices.size());
        icicle.setVBufferIdx(buf_idx);
        icicle.setVStartIdx(0);
        icicle.setVLength(verts.size());
        icicle.setCellIdx(0);
        icicle.setCellOffset(0);
        icicle.setLocalToWorld(span->getLocalToWorld());
        icicle.setWorldToLocal(span->getWorldToLocal());
        icicle.setMaterialIdx(mat_idx);
        icicle.setGroupIdx(groups[format].second);
        uint32_t props = plSpan::deswizzleGeoFlags(span->getProps());
        if (span->getPermaLights().size() > 0)
            props |= plSpan::kPropHasPermaLights;
        if (span->getPermaProjs().size() > 0)
            props |= plSpan::kPropHasPermaProjs;
        icicle.setProps(props);
        icicle.setBaseMatrix(span->getBaseMatrix());
        icicle.setFogEnvironment(span->getFogEnvironment());
        icicle.setLocalBounds(span->getLocalBounds());
        icicle.setWorldBounds(span->getWorldBounds());
        icicle.setLocalUVWChans(span->getLocalUVWChans());
        icicle.setMaxBoneIdx(span->getMaxBoneIdx());
        icicle.setMinDist(span->getMinDist());
        icicle.setMaxDist(span->getMaxDist());
        icicle.setWaterHeight(span->getWaterHeight());
        icicle.setPenBoneIdx(span->getPenBoneIdx());
        icicle.setNumMatrices(span->getNumMatrices());
        icicle.setPermaLights(span->getPermaLights());
        icicle.setPermaProjs(span->getPermaProjs());
        addIcicle(icicle);
    }

    if (calcbounds)
        calcBounds();
    BuildSpaceTree();

    if (clearspans)
        fSourceSpans.clear();
}

void plDrawableSpans::decomposeGeometry(bool clearcolors) {
    for (size_t i=0; i<fIcicles.size(); i++) {
        plIcicle* icicle = fIcicles[i];
        plGeometrySpan* span = new plGeometrySpan();
        plGBufferGroup* group = fGroups[icicle->getGroupIdx()];

        span->setLocalToWorld(icicle->getLocalToWorld());
        span->setWorldToLocal(icicle->getWorldToLocal());
        span->setLocalBounds(icicle->getLocalBounds());
        span->setWorldBounds(icicle->getWorldBounds());
        span->setMaterial(fMaterials[icicle->getMaterialIdx()]);
        span->setFogEnvironment(icicle->getFogEnvironment());
        span->setMinDist(icicle->getMinDist());
        span->setMaxDist(icicle->getMaxDist());
        span->setNumMatrices(icicle->getNumMatrices());
        span->setProps(plSpan::swizzleGeoFlags(icicle->getProps()));
        span->setBaseMatrix(icicle->getBaseMatrix());
        span->setLocalUVWChans(icicle->getLocalUVWChans());
        span->setMaxBoneIdx(icicle->getMaxBoneIdx());
        span->setWaterHeight(icicle->getWaterHeight());
        span->setPenBoneIdx(icicle->getPenBoneIdx());
        span->setPermaLights(icicle->getPermaLights());
        span->setPermaProjs(icicle->getPermaProjs());

        span->setFormat(group->getFormat());

        std::vector<unsigned short> indices;
        indices = group->getIndices(icicle->getIBufferIdx(),
                                    icicle->getIStartIdx(),
                                    icicle->getILength());
        for (size_t j=0; j<indices.size(); j++)
            indices[j] -= icicle->getVStartIdx();

        span->setIndices(indices);

        std::vector<plGBufferVertex> vertices;
        std::vector<plGeometrySpan::TempVertex> new_vertices;
        vertices = group->getVertices(icicle->getVBufferIdx(),
                                      icicle->getVStartIdx(),
                                      icicle->getVLength());
        new_vertices.resize(vertices.size());
        for (size_t j=0; j<vertices.size(); j++) {
            plGBufferVertex v1 = vertices[j];
            plGeometrySpan::TempVertex v2;
            v2.fPosition = v1.fPos;
            v2.fNormal = v1.fNormal;
            for (size_t k=0; k<8; k++) {
                v2.fUVs[k] = v1.fUVWs[k];
            }
            for (size_t k=0; k<3; k++) {
                v2.fWeights[k] = v1.fSkinWeights[k];
            }
            v2.fIndices = v1.fSkinIdx;
            if (clearcolors)
                v2.fColor = 0xFFFFFFFF;
            else
                v2.fColor = v1.fColor;
            v2.fSpecularColor = 0;
            v2.fAddColor = hsColorRGBA::kBlack;
            v2.fMultColor = hsColorRGBA::kWhite;
            new_vertices[j] = v2;
        }
        span->setVertices(new_vertices);
        fSourceSpans.push_back(span);
    }
}

size_t plDrawableSpans::buildDIIndex(const std::vector<plGeometrySpan*>& spans) {
    plDISpanIndex di_idx;
    for (size_t i=0; i<spans.size(); ++i) {
        auto span_f = std::find(fSourceSpans.begin(), fSourceSpans.end(), spans[i]);
        if (span_f == fSourceSpans.end())
            di_idx.fIndices.push_back(-1);
        else
            di_idx.fIndices.push_back(span_f - fSourceSpans.begin());
    }
    size_t result = fDIIndices.size();
    fDIIndices.push_back(di_idx);
    return result;
}

size_t plDrawableSpans::addSourceSpan(plGeometrySpan* span)
{
    fSourceSpans.push_back(span);
    return fSourceSpans.size() - 1;
}
