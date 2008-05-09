#include "plSpawnPointInfo.h"
#include "CoreLib/hsBitVector.h"

plSpawnPointInfo::plSpawnPointInfo() { }
plSpawnPointInfo::~plSpawnPointInfo() { }

void plSpawnPointInfo::read(hsStream* S) {
    hsBitVector flags;
    flags.read(S);
    if (flags[kHasTitle]) {
        size_t len = S->readShort();
        fTitle = S->readStr(len);
    }
    if (flags[kHasSpawnPt]) {
        size_t len = S->readShort();
        fSpawnPt = S->readStr(len);
    }
    if (flags[kHasCameraStack]) {
        size_t len = S->readShort();
        fCameraStack = S->readStr(len);
    }
}

void plSpawnPointInfo::write(hsStream* S) {
    hsBitVector flags;
    flags[kHasTitle] = true;
    flags[kHasSpawnPt] = true;
    flags[kHasCameraStack] = true;
    flags.write(S);

    S->writeShort(fTitle.len());
    S->writeStr(fTitle);
    S->writeShort(fSpawnPt.len());
    S->writeStr(fSpawnPt);
    S->writeShort(fCameraStack.len());
    S->writeStr(fCameraStack);
}

void plSpawnPointInfo::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plSpawnPointInfo");
    prc->writeParam("Title", fTitle);
    prc->writeParam("SpawnPoint", fSpawnPt);
    prc->writeParam("CameraStack", fCameraStack);
    prc->endTag(true);
}

void plSpawnPointInfo::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plSpawnPointInfo")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fTitle = tag->getParam("Title", "");
    fSpawnPt = tag->getParam("SpawnPoint", "");
    fCameraStack = tag->getParam("CameraStack", "");
}

bool plSpawnPointInfo::isEmpty() {
    return (fTitle.empty() && fSpawnPt.empty() && fCameraStack.empty());
}
