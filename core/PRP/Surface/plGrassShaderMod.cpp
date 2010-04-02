#include "plGrassShaderMod.h"

/* plGrassWave */
plGrassWave::plGrassWave() : fDistX(0.0f), fDistY(0.0f), fDistZ(0.0f),
                             fDirX(0.0f), fDirY(0.0f), fSpeed(0.0f) { }

void plGrassWave::read(hsStream* S) {
    fDistX = S->readFloat();
    fDistY = S->readFloat();
    fDistZ = S->readFloat();
    fDirX = S->readFloat();
    fDirY = S->readFloat();
    fSpeed = S->readFloat();
}

void plGrassWave::write(hsStream* S) {
    S->writeFloat(fDistX);
    S->writeFloat(fDistY);
    S->writeFloat(fDistZ);
    S->writeFloat(fDirX);
    S->writeFloat(fDirY);
    S->writeFloat(fSpeed);
}

void plGrassWave::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plGrassWave");
    prc->writeParam("DistX", fDistX);
    prc->writeParam("DistY", fDistY);
    prc->writeParam("DistZ", fDistZ);
    prc->writeParam("DirX", fDirX);
    prc->writeParam("DirY", fDirY);
    prc->writeParam("Speed", fSpeed);
    prc->endTag(true);
}

void plGrassWave::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plGrassWave")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fDistX = tag->getParam("DistX", "0").toFloat();
    fDistY = tag->getParam("DistY", "0").toFloat();
    fDistZ = tag->getParam("DistZ", "0").toFloat();
    fDirX = tag->getParam("DirX", "0").toFloat();
    fDirY = tag->getParam("DirY", "0").toFloat();
    fSpeed = tag->getParam("Speed", "0").toFloat();
}


/* plGrassShaderMod */
void plGrassShaderMod::read(hsStream* S, plResManager* mgr) {
    plModifier::read(S, mgr);

    fMaterial = mgr->readKey(S);
    for (size_t i=0; i<kNumWaves; i++)
        fWaves[i].read(S);
}

void plGrassShaderMod::write(hsStream* S, plResManager* mgr) {
    plModifier::write(S, mgr);

    mgr->writeKey(S, fMaterial);
    for (size_t i=0; i<kNumWaves; i++)
        fWaves[i].write(S);
}

void plGrassShaderMod::IPrcWrite(pfPrcHelper* prc) {
    plModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Material");
    fMaterial->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Waves");
    for (size_t i=0; i<kNumWaves; i++)
        fWaves[i].prcWrite(prc);
    prc->closeTag();
}

void plGrassShaderMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Material") {
        if (tag->hasChildren())
            fMaterial = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Waves") {
        if (tag->countChildren() != kNumWaves)
            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of waves");

        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<kNumWaves; i++) {
            fWaves[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plModifier::IPrcParse(tag, mgr);
    }
}
