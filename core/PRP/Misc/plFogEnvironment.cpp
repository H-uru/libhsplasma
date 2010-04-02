#include "plFogEnvironment.h"

const char* const plFogEnvironment::FogTypeNames[] = {
    "Linear", "Exp", "Exp2", "None"
};

plFogEnvironment::plFogEnvironment()
                : fType(kLinearFog), fStart(1.0f), fEnd(1000.0f), fDensity(0.5f) { }

void plFogEnvironment::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    fType = S->readByte();
    fStart = S->readFloat();
    fEnd = S->readFloat();
    fDensity = S->readFloat();
    fColor.read(S);
}

void plFogEnvironment::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    S->writeByte(fType);
    S->writeFloat(fStart);
    S->writeFloat(fEnd);
    S->writeFloat(fDensity);
    fColor.write(S);
}

void plFogEnvironment::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("FogParams");
    prc->writeParam("Type", FogTypeNames[fType]);
    prc->writeParam("Start", fStart);
    prc->writeParam("End", fEnd);
    prc->writeParam("Density", fDensity);
    prc->endTag(true);

    prc->writeSimpleTag("Color");
    fColor.prcWrite(prc);
    prc->closeTag();
}

void plFogEnvironment::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "FogParams") {
        plString fogTypeName = tag->getParam("Type", "");
        fType = kNoFog;
        for (size_t i=0; i<=kNoFog; i++) {
            if (fogTypeName == FogTypeNames[i])
                fType = i;
        }
        fStart = tag->getParam("Start", "0").toFloat();
        fEnd = tag->getParam("End", "0").toFloat();
        fDensity = tag->getParam("Density", "0").toFloat();
    } else if (tag->getName() == "Color") {
        if (tag->hasChildren())
            fColor.prcParse(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
