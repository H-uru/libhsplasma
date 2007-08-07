#include "plDirectionalLightInfo.h"

// plDirectionalLightInfo //
plDirectionalLightInfo::plDirectionalLightInfo() { }
plDirectionalLightInfo::~plDirectionalLightInfo() { }

IMPLEMENT_CREATABLE(plDirectionalLightInfo, kDirectionalLightInfo, plLightInfo)

void plDirectionalLightInfo::read(hsStream* S) { plLightInfo::read(S); }
void plDirectionalLightInfo::write(hsStream* S) { plLightInfo::write(S); }
void plDirectionalLightInfo::prcWrite(pfPrcHelper* prc) {
    plObjInterface::prcWrite(prc);
}


// plLimitedDirLightInfo //
plLimitedDirLightInfo::plLimitedDirLightInfo() { }
plLimitedDirLightInfo::~plLimitedDirLightInfo() { }

IMPLEMENT_CREATABLE(plLimitedDirLightInfo, kLimitedDirLightInfo,
                    plDirectionalLightInfo)

void plLimitedDirLightInfo::read(hsStream* S) {
    plDirectionalLightInfo::read(S);
    fWidth = S->readFloat();
    fHeight = S->readFloat();
    fDepth = S->readFloat();
}

void plLimitedDirLightInfo::write(hsStream* S) {
    plDirectionalLightInfo::write(S);
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

