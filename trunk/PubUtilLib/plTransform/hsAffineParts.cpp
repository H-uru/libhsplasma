#include "hsAffineParts.h"

hsAffineParts::hsAffineParts() : fI(0) { }

void hsAffineParts::read(hsStream* S) {
    if (S->getVer() != pvLive)
        fI = S->readInt();
    fT.read(S);
    fQ.read(S);
    fU.read(S);
    fK.read(S);
    fF = S->readFloat();
}

void hsAffineParts::write(hsStream* S) {
    if (S->getVer() != pvLive)
        S->writeInt(fI);
    fT.write(S);
    fQ.write(S);
    fU.write(S);
    fK.write(S);
    S->writeFloat(fF);
}

void hsAffineParts::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("hsAffineParts");
      prc->startTag("I");
      prc->writeParam("value", fI);
      prc->endTag(true);
      prc->writeSimpleTag("T");
        fT.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("Q");
        fQ.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("U");
        fU.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("K");
        fK.prcWrite(prc);
      prc->closeTag();
      prc->startTag("F");
      prc->writeParam("value", fF);
      prc->endTag(true);
    prc->closeTag();
}
