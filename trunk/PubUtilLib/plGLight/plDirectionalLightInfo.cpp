#include "plDirectionalLightInfo.h"

// plDirectionalLightInfo //
plDirectionalLightInfo::plDirectionalLightInfo() { }
plDirectionalLightInfo::~plDirectionalLightInfo() { }

IMPLEMENT_CREATABLE(plDirectionalLightInfo, kDirectionalLightInfo, plLightInfo)

void plDirectionalLightInfo::read(hsStream* S, plResManager* mgr) {
    plLightInfo::read(S, mgr);
}

void plDirectionalLightInfo::write(hsStream* S, plResManager* mgr) {
    plLightInfo::write(S, mgr);
}

void plDirectionalLightInfo::prcWrite(pfPrcHelper* prc) {
    plLightInfo::prcWrite(prc);
}


// plLimitedDirLightInfo //
plLimitedDirLightInfo::plLimitedDirLightInfo() { }
plLimitedDirLightInfo::~plLimitedDirLightInfo() { }

IMPLEMENT_CREATABLE(plLimitedDirLightInfo, kLimitedDirLightInfo,
                    plDirectionalLightInfo)

void plLimitedDirLightInfo::read(hsStream* S, plResManager* mgr) {
    plDirectionalLightInfo::read(S, mgr);
    fWidth = S->readFloat();
    fHeight = S->readFloat();
    fDepth = S->readFloat();
}

void plLimitedDirLightInfo::write(hsStream* S, plResManager* mgr) {
    plDirectionalLightInfo::write(S, mgr);
    S->writeFloat(fWidth);
    S->writeFloat(fHeight);
    S->writeFloat(fDepth);
}

void plLimitedDirLightInfo::prcWrite(pfPrcHelper* prc) {
    plDirectionalLightInfo::prcWrite(prc);
    prc->startTag("Limits");
    prc->writeParam("Width", fWidth);
    prc->writeParam("Height", fHeight);
    prc->writeParam("Depth", fDepth);
    prc->endTag(true);
}
