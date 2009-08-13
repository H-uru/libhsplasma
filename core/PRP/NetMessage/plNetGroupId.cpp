#include "plNetGroupId.h"

plNetGroupId::plNetGroupId() : fFlags(0) { }

void plNetGroupId::read(hsStream* S) {
    fID.read(S);
    fFlags = S->readByte();
}

void plNetGroupId::write(hsStream* S) {
    fID.write(S);
    S->writeByte(fFlags);
}

void plNetGroupId::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plNetGroupId");
    prc->writeParam("Flags", fFlags);
    prc->endTag();
    fID.prcWrite(prc);
    prc->closeTag();
}

void plNetGroupId::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plNetGroupId")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fFlags = tag->getParam("Flags", "0").toUint();
    if (tag->hasChildren())
        fID.prcParse(tag->getFirstChild());
}
