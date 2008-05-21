#include "plExcludeRegionModifier.h"

plExcludeRegionModifier::plExcludeRegionModifier() : fSeek(false) {
    fFlags.setName(kBlockCameras, "kBlockCameras");
}

plExcludeRegionModifier::~plExcludeRegionModifier() { }

IMPLEMENT_CREATABLE(plExcludeRegionModifier, kExcludeRegionModifier,
                    plSingleModifier)

void plExcludeRegionModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fSafePoints.setSize(S->readInt());
    for (size_t i=0; i<fSafePoints.getSize(); i++)
        fSafePoints[i] = mgr->readKey(S);
    fSeek = S->readBool();
    fSeekTime = S->readFloat();
}

void plExcludeRegionModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fSafePoints.getSize());
    for (size_t i=0; i<fSafePoints.getSize(); i++)
        mgr->writeKey(S, fSafePoints[i]);
    S->writeBool(fSeek);
    S->writeFloat(fSeekTime);
}

void plExcludeRegionModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("ExcludeRegionParams");
    prc->writeParam("Seek", fSeek);
    prc->writeParam("SeekTime", fSeekTime);
    prc->endTag(true);

    prc->writeSimpleTag("SafePoints");
    for (size_t i=0; i<fSafePoints.getSize(); i++)
        fSafePoints[i]->prcWrite(prc);
    prc->closeTag();
}

void plExcludeRegionModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ExcludeRegionParams") {
        fSeek = tag->getParam("Seek", "false").toBool();
        fSeekTime = tag->getParam("SeekTime", "0").toFloat();
    } else if (tag->getName() == "SafePoints") {
        fSafePoints.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSafePoints.getSize(); i++) {
            fSafePoints[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
