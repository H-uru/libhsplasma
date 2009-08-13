#include "hsAffineParts.h"

hsAffineParts::hsAffineParts()
             : fI(0), fK(1.0f, 1.0f, 1.0f), fF(1.0f) { }

hsAffineParts::hsAffineParts(const hsAffineParts& init)
             : fI(init.fI), fT(init.fT), fQ(init.fQ), fU(init.fU),
               fK(init.fK), fF(init.fF) { }

void hsAffineParts::read(hsStream* S) {
    fI = (S->getVer() != pvLive) ? S->readInt() : 0;
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

void hsAffineParts::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsAffineParts")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "I") {
            fI = child->getParam("value", "0").toInt();
        } else if (child->getName() == "T") {
            if (child->hasChildren())
                fT.prcParse(child->getFirstChild());
        } else if (child->getName() == "Q") {
            if (child->hasChildren())
                fQ.prcParse(child->getFirstChild());
        } else if (child->getName() == "U") {
            if (child->hasChildren())
                fU.prcParse(child->getFirstChild());
        } else if (child->getName() == "K") {
            if (child->hasChildren())
                fK.prcParse(child->getFirstChild());
        } else if (child->getName() == "F") {
            fF = child->getParam("value", "0").toFloat();
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}
