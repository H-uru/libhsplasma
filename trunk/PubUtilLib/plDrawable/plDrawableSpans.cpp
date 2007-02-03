#include "plDrawableSpans.h"
#include "../plResMgr/plResManager.h"

/* plDrawable */
plDrawable::plDrawable(PlasmaVer pv) { }
plDrawable::~plDrawable() { }

short plDrawable::ClassIndex() { return 0x0017; }


/* plDrawableSpans */
plDrawableSpans::plDrawableSpans(PlasmaVer pv) { }
plDrawableSpans::~plDrawableSpans() { }

short plDrawableSpans::ClassIndex() {
    return (ver == pvEoa ? 0x0049 : 0x004C);
}

void plDrawableSpans::read(hsStream* S) {
    hsKeyedObject::read(S);
    bool gotSkin = false;

    props = S->readInt();
    criteria = S->readInt();
    renderLevel.level = S->readInt();

    int i, j, count, count2;
    
    count = S->readInt();
    materials.setSize(count);
    for (i=0; i<count; i++)
        materials[i] = (hsGMaterial*)plResManager::inst->readKey(S)->objPtr;

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
    for (i=0; i<count; i++) {
        unsigned int idx = S->readInt();
        if (idx & 0xC0000000) {
          if (idx & 0xC0000000 == 0xC0000000)
              spans.append(((plSpan*&)particleSpans[idx & 0x3FFFFFFF]));
        } else {
            spans.append((plSpan*&)icicles[idx & 0x3FFFFFFF]);
        }
        spanSourceIndices.append(idx);
        if (spans[spans.getSize()-1]->getTypeMask() & plSpan::kParticleSpan) {
            plParticleSpan* ps = (plParticleSpan*)spans[spans.getSize()-1];
            ps->setSrcSpanIdx(spans.getSize()-1);
        }
    }
    //IBuildVectors();

    for (int i=0; i<count; i++)
        spans[i]->setFogEnviron(plResManager::inst->readKey(S));

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
                spans[i]->setPermaLight(plResManager::inst->readKey(S));
        }
        if (spans[i]->getProps() & plSpan::kPropHasPermaProjs) {
            count2 = S->readInt();
            for (j=0; j<count2; j++)
                spans[i]->setPermaProj(plResManager::inst->readKey(S));
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
        DIIndices[i] = new plDISpanIndex;
        DIIndices[i]->flags = S->readInt();

        count2 = S->readInt();
        DIIndices[i]->indices.setSize(count2);
        for (j=0; j<count2; j++)
            DIIndices[i]->indices[j] = S->readInt();
    }

    count = S->readInt();
    for (i=0; i<count; i++) {
        plGBufferGroup* bg = new plGBufferGroup(0, props & kPropVolatile, props & kPropSortFaces, 0);
        bg->read(S);
        groups.append(bg);
    }

    if (props & kPropSortFaces) {
        for (i=0; i<spans.getSize(); i++) {
            if (spans[i]->getProps() & plSpan::kPropFacesSortable) {
                plIcicle* icicle = (plIcicle*)spans[i];
                groups[icicle->groupIdx]->ConvertToTriList(i, icicle->IBufferIdx,
                        icicle->VBufferIdx, icicle->cellIdx, icicle->IStartIdx,
                        icicle->ILength / 3);
            }
        }
    }

    spaceTree = new plSpaceTree(ver);
    spaceTree->read(S);
    sceneNode = plResManager::inst->readKey(S);

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

void plDrawableSpans::write(hsStream* S) {
    //if (needCleanup)
    //    IRemoveGarbage();
    hsKeyedObject::write(S);

    S->writeInt(props);
    S->writeInt(criteria);
    S->writeInt(renderLevel.level);

    int i;
    S->writeInt(materials.getSize());
    for (i=0; i<materials.getSize(); i++)
        plResManager::inst->writeKey(S, materials[i]->getKey());

    S->writeInt(icicles.getSize());
    for (i=0; i<icicles.getSize(); i++)
        icicles[i].write(S);

    S->writeInt(0);  // No Icicles2

    throw "Incomplete";
}
