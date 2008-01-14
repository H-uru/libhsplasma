#include "plShadowMaster.h"

/* plShadowMaster */
plShadowMaster::plShadowMaster()
              : fAttenDist(0.0f), fMaxDist(0.0f), fMinDist(0.0f), fPower(0.0f),
                fMaxSize(0), fMinSize(0), fLightInfo(NULL) {
    Props.setName(kDisable, "kDisable");
    Props.setName(kSelfShadow, "kSelfShadow");
}

plShadowMaster::~plShadowMaster() {
    for (size_t i=0; i<fSlavePool.getSize(); i++)
        delete fSlavePool[i];
}

IMPLEMENT_CREATABLE(plShadowMaster, kShadowMaster, plObjInterface)

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

void plShadowMaster::prcWrite(pfPrcHelper* prc) {
    plObjInterface::prcWrite(prc);

    prc->startTag("ShadowParams");
    prc->writeParam("AttenDist", fAttenDist);
    prc->writeParam("MaxDist", fMaxDist);
    prc->writeParam("MinDist", fMinDist);
    prc->writeParam("MaxSize", fMaxSize);
    prc->writeParam("MinSize", fMinSize);
    prc->writeParam("Power", fPower);
    prc->endTag(true);
}


/* plPointShadowMaster */
plPointShadowMaster::plPointShadowMaster() { }
plPointShadowMaster::~plPointShadowMaster() { }

IMPLEMENT_CREATABLE(plPointShadowMaster, kPointShadowMaster, plShadowMaster)


/* plDirectShadowMaster */
plDirectShadowMaster::plDirectShadowMaster() { }

plDirectShadowMaster::~plDirectShadowMaster() {
    for (size_t i=0; i<fPerspSlavePool.getSize(); i++)
        delete fPerspSlavePool[i];
}

IMPLEMENT_CREATABLE(plDirectShadowMaster, kDirectShadowMaster, plShadowMaster)
