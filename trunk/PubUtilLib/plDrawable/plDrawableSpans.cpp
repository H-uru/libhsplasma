#include "plDrawableSpans.h"
#include "../plResMgr/plResManager.h"

/* plDrawable */
plDrawable::plDrawable() { }
plDrawable::~plDrawable() { }

IMPLEMENT_CREATABLE(plDrawable, kDrawable, hsKeyedObject)


/* plDrawableSpans */
plDrawableSpans::plDrawableSpans() { }
plDrawableSpans::~plDrawableSpans() {
    size_t i;
    for (i=0; i<sourceSpans.getSize(); i++)
        delete sourceSpans[i];
    sourceSpans.clear();
    for (i=0; i<DIIndices.getSize(); i++)
        delete DIIndices[i];
    DIIndices.clear();
    for (i=0; i<groups.getSize(); i++)
        delete groups[i];
    groups.clear();
    if (spaceTree != NULL) delete spaceTree;
}

IMPLEMENT_CREATABLE(plDrawableSpans, kDrawableSpans, plDrawable)

void plDrawableSpans::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    bool gotSkin = false;

    props = S->readInt();
    criteria = S->readInt();
    renderLevel.level = S->readInt();

    size_t i, j, count, count2;
    
    count = S->readInt();
    materials.setSize(count);
    for (i=0; i<count; i++)
        materials[i] = mgr->readKey(S);

    count = S->readInt();
    icicles.setSize(count);
    for (i=0; i<count; i++) {
        icicles[i].read(S);
        if (icicles[i].getNumMatrices() != 0)
            gotSkin = true;
    }
    S->readInt(); // Discarded -- Icicles2

    spanSourceIndices.clear();
    spans.clear();

    count = S->readInt();
    spans.setSizeNull(count);
    spanSourceIndices.setSizeNull(count);
    for (i=0; i<count; i++) {
        unsigned int idx = S->readInt();
        if ((idx & kSpanTypeMask) == kSpanTypeIcicle)
            spans[i] = &(icicles[idx & kSpanIDMask]);
        else if ((idx & kSpanTypeMask) == kSpanTypeParticleSpan)
            spans[i] = &(particleSpans[idx & kSpanIDMask]);
        spanSourceIndices[i] = idx;
        //if (spans[spans.getSize()-1]->getTypeMask() & plSpan::kParticleSpan) {
        //    plParticleSpan* ps = (plParticleSpan*)spans[spans.getSize()-1];
        //    ps->setSrcSpanIdx(spans.getSize()-1);
        //}
    }
    //IBuildVectors();

    for (i=0; i<count; i++)
        spans[i]->setFogEnvironment(mgr->readKey(S));

    if (count > 0) {
        localBounds.read(S);
        worldBounds.read(S);
        maxWorldBounds.read(S);
    } else {
        localBounds.setType(hsBounds3::kIsSphere);
        worldBounds.setType(hsBounds3::kIsSphere);
        maxWorldBounds.setType(hsBounds3::kIsSphere);
    }

    for (i=0; i<count; i++) {
        if (spans[i]->getProps() & plSpan::kPropHasPermaLights) {
            count2 = S->readInt();
            for (j=0; j<count2; j++)
                spans[i]->addPermaLight(mgr->readKey(S));
        }
        if (spans[i]->getProps() & plSpan::kPropHasPermaProjs) {
            count2 = S->readInt();
            for (j=0; j<count2; j++)
                spans[i]->addPermaProj(mgr->readKey(S));
        }
    }

    count = S->readInt();
    if (count > 0) {
        sourceSpans.setSize(count);
        for (i=0; i<count; i++) {
            sourceSpans[i] = new plGeometrySpan;
            sourceSpans[i]->read(S);
            if (spans[i]->getMaterialIdx() == 0xFFFFFFFF)
                sourceSpans[i]->setMaterial(NULL);
            else
                sourceSpans[i]->setMaterial(materials[spans[i]->getMaterialIdx()]);
            sourceSpans[i]->setFogEnvironment(spans[i]->getFogEnvironment());
            //sourceSpans[i]->setSpanRefIndex(i);
        }
    } else {
        sourceSpans.clear();
    }

    count = S->readInt();
    localToWorlds.setSize(count);
    worldToLocals.setSize(count);
    localToBones.setSize(count);
    boneToLocals.setSize(count);
    for (i=0; i<count; i++) {
        localToWorlds[i].read(S);
        worldToLocals[i].read(S);
        localToBones[i].read(S);
        boneToLocals[i].read(S);
    }

    count = S->readInt();
    DIIndices.setSize(count);
    for (i=0; i<count; i++) {
        DIIndices[i] = new plDISpanIndex();
        DIIndices[i]->flags = S->readInt();

        count2 = S->readInt();
        DIIndices[i]->indices.setSize(count2);
        for (j=0; j<count2; j++)
            DIIndices[i]->indices[j] = S->readInt();
    }

    count = S->readInt();
    groups.setSize(count);
    for (i=0; i<count; i++) {
        groups[i] = new plGBufferGroup(0, props & kPropVolatile, props & kPropSortFaces, 0);
        groups[i]->read(S);
    }

    /*
    if (props & kPropSortFaces) {
        for (i=0; i<spans.getSize(); i++)
            IMakeSpanSortable(i);
    }
    */

    spaceTree = plSpaceTree::Convert(mgr->ReadCreatable(S));
    sceneNode = mgr->readKey(S);

    /*
    if (GetNativeProperty(kPropCharacter)) {
        if (visSet.numBitVectors <= 0)
            visSet.IGrow(1);
        visSet.setBit(1);
        for (int i=0; i<spans.getCount(); i++) {
            if (spans[i]->visSet.numBitVectors <= 0)
                spans[i]->visSet.IGrow(1);
            spans[i]->visSet.setBit(1);
        }
    }
    */
    
    if (gotSkin)
        registeredForRender = true;
    readyToRender = false;
}

void plDrawableSpans::write(hsStream* S, plResManager* mgr) {
    //if (needCleanup)
    //    IRemoveGarbage();
    hsKeyedObject::write(S, mgr);

    S->writeInt(props);
    S->writeInt(criteria);
    S->writeInt(renderLevel.level);

    size_t i, j;
    S->writeInt(materials.getSize());
    for (i=0; i<materials.getSize(); i++)
        mgr->writeKey(S, materials[i]);

    S->writeInt(icicles.getSize());
    for (i=0; i<icicles.getSize(); i++)
        icicles[i].write(S);

    S->writeInt(0);  // No Icicles2

    S->writeInt(spanSourceIndices.getSize());
    for (i=0; i<spanSourceIndices.getSize(); i++)
        S->writeInt(spanSourceIndices[i]);
    
    for (i=0; i<spans.getSize(); i++)
        mgr->writeKey(S, spans[i]->getFogEnvironment());

    if (spans.getSize() > 0) {
        localBounds.write(S);
        worldBounds.write(S);
        maxWorldBounds.write(S);
    }

    for (i=0; i<spans.getSize(); i++) {
        if (spans[i]->getProps() & plSpan::kPropHasPermaLights) {
            S->writeInt(spans[i]->getPermaLights().getSize());
            for (j=0; j<spans[i]->getPermaLights().getSize(); j++)
                mgr->writeKey(S, spans[i]->getPermaLights()[j]);
        }
        if (spans[i]->getProps() & plSpan::kPropHasPermaProjs) {
            S->writeInt(spans[i]->getPermaProjs().getSize());
            for (j=0; j<spans[i]->getPermaProjs().getSize(); j++)
                mgr->writeKey(S, spans[i]->getPermaProjs()[j]);
        }
    }

    S->writeInt(sourceSpans.getSize());
    for (i=0; i<sourceSpans.getSize(); i++)
        sourceSpans[i]->write(S);

    S->writeInt(localToWorlds.getSize());
    for (i=0; i<localToWorlds.getSize(); i++) {
        localToWorlds[i].write(S);
        worldToLocals[i].write(S);
        localToBones[i].write(S);
        boneToLocals[i].write(S);
    }

    S->writeInt(DIIndices.getSize());
    for (i=0; i<DIIndices.getSize(); i++) {
        S->writeInt(DIIndices[i]->flags);
        S->writeInt(DIIndices[i]->indices.getSize());
        for (j=0; j<DIIndices[i]->indices.getSize(); j++)
            S->writeInt(DIIndices[i]->indices[j]);
    }

    S->writeInt(groups.getSize());
    for (i=0; i<groups.getSize(); i++)
        groups[i]->write(S);

    mgr->WriteCreatable(S, spaceTree);
    mgr->writeKey(S, sceneNode);
}

void plDrawableSpans::prcWrite(pfPrcHelper* prc) {
    hsKeyedObject::prcWrite(prc);

    prc->startTag("Properties");
    prc->writeParam("Flags", props);
    prc->writeParam("Criteria", criteria);
    prc->writeParam("RenderLevel", renderLevel.level);
    prc->endTag(true);

    size_t i, j;
    prc->writeSimpleTag("Materials");
    for (i=0; i<materials.getSize(); i++)
        materials[i]->prcWrite(prc);
    prc->closeTag();
    
    prc->writeSimpleTag("Icicles");
    for (i=0; i<icicles.getSize(); i++) {
        icicles[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
    
    prc->writeSimpleTag("SpanSourceIndices");
    for (i=0; i<spanSourceIndices.getSize(); i++) {
        prc->startTag("SourceIndex");
        prc->writeParam("value", spanSourceIndices[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("FogEnvironments");
    for (i=0; i<spans.getSize(); i++) {
        if (spans[i]->getFogEnvironment() == NULL)
            prc->writeComment("Null Fog Environment");
        else
            spans[i]->getFogEnvironment()->prcWrite(prc);
    }
    prc->closeTag();

    prc->writeSimpleTag("Bounds");
    if (spans.getSize() > 0) {
        prc->writeComment("Local, World, MaxWorld");
        localBounds.prcWrite(prc);
        prc->closeTag();
        worldBounds.prcWrite(prc);
        prc->closeTag();
        maxWorldBounds.prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("PermaLightInfo");
    for (i=0; i<spans.getSize(); i++) {
        prc->startTag("Span");
        prc->writeParam("idx", i);
        prc->endTag();
        if (spans[i]->getProps() & plSpan::kPropHasPermaLights) {
            prc->writeSimpleTag("PermaLights");
            for (j=0; j<spans[i]->getPermaLights().getSize(); j++)
                spans[i]->getPermaLights()[j]->prcWrite(prc);
            prc->closeTag();
        }
        if (spans[i]->getProps() & plSpan::kPropHasPermaProjs) {
            prc->writeSimpleTag("PermaProjs");
            for (j=0; j<spans[i]->getPermaProjs().getSize(); j++)
                spans[i]->getPermaProjs()[j]->prcWrite(prc);
            prc->closeTag();
        }
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("SourceSpans");
    for (i=0; i<sourceSpans.getSize(); i++)
        sourceSpans[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Transforms");
    for (i=0; i<localToWorlds.getSize(); i++) {
        prc->writeSimpleTag("LocalToWorld");
        localToWorlds[i].prcWrite(prc);
        worldToLocals[i].prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("LocalToBone");
        localToBones[i].prcWrite(prc);
        boneToLocals[i].prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("DIIndices");
    for (i=0; i<DIIndices.getSize(); i++) {
        prc->startTag("plDISpanIndex");
        prc->writeParam("flags", DIIndices[i]->flags);
        prc->endTag();
        for (j=0; j<DIIndices[i]->indices.getSize(); j++) {
            prc->startTag("Index");
            prc->writeParam("value", DIIndices[i]->indices[j]);
            prc->endTag(true);
        }
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("BufferGroups");
    for (i=0; i<groups.getSize(); i++)
        groups[i]->prcWrite(prc);
    prc->closeTag();

    if (spaceTree != NULL) {
        spaceTree->prcWrite(prc);
        prc->closeTag();
    }

    prc->writeSimpleTag("SceneNode");
    sceneNode->prcWrite(prc);
    prc->closeTag();
}

