#include "plShadowMaster.h"

/* plShadowMaster */
plShadowMaster::plShadowMaster()
              : fAttenDist(0.0f), fMaxDist(0.0f), fMinDist(0.0f), fPower(0.0f),
                fMaxSize(0), fMinSize(0) {
    fProps.setName(kDisable, "kDisable");
    fProps.setName(kSelfShadow, "kSelfShadow");
}

void plShadowMaster::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);

    fAttenDist = S->readFloat();
    fMaxDist = S->readFloat();
    fMinDist = S->readFloat();
    fMaxSize = S->readInt();
    fMinSize = S->readInt();
    fPower = S->readFloat();
}

void plShadowMaster::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    S->writeFloat(fAttenDist);
    S->writeFloat(fMaxDist);
    S->writeFloat(fMinDist);
    S->writeInt(fMaxSize);
    S->writeInt(fMinSize);
    S->writeFloat(fPower);
}

void plShadowMaster::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->startTag("ShadowParams");
    prc->writeParam("AttenDist", fAttenDist);
    prc->writeParam("MaxDist", fMaxDist);
    prc->writeParam("MinDist", fMinDist);
    prc->writeParam("MaxSize", fMaxSize);
    prc->writeParam("MinSize", fMinSize);
    prc->writeParam("Power", fPower);
    prc->endTag(true);
}

void plShadowMaster::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ShadowParams") {
        fAttenDist = tag->getParam("AttenDist", "0").toFloat();
        fMaxDist = tag->getParam("MaxDist", "0").toFloat();
        fMinDist = tag->getParam("MinDist", "0").toFloat();
        fMaxSize = tag->getParam("MaxSize", "0").toUint();
        fMinSize = tag->getParam("MinSize", "0").toUint();
        fPower = tag->getParam("Power", "0").toFloat();
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
