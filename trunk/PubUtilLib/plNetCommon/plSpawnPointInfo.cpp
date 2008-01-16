#include "plSpawnPointInfo.h"
#include "../../CoreLib/hsBitVector.h"

plSpawnPointInfo::plSpawnPointInfo() { }
plSpawnPointInfo::~plSpawnPointInfo() { }

void plSpawnPointInfo::read(hsStream* S) {
    hsBitVector flags;
    flags.read(S);
    if (flags[0]) {
        size_t len = S->readShort();
        fTitle = S->readStr(len);
    }
    if (flags[1]) {
        size_t len = S->readShort();
        fSpawnPt = S->readStr(len);
    }
    if (flags[2]) {
        size_t len = S->readShort();
        fCameraStack = S->readStr(len);
    }
}

void plSpawnPointInfo::write(hsStream* S) {
    hsBitVector flags;
    flags.setBit(0);
    flags.setBit(1);
    flags.setBit(2);
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
    prc->writeParam("SpawnPt", fSpawnPt);
    prc->writeParam("CameraStack", fCameraStack);
    prc->endTag(true);
}
