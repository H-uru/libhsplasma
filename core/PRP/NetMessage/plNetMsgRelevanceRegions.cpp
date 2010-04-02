#include "plNetMsgRelevanceRegions.h"

void plNetMsgRelevanceRegions::read(hsStream* S, plResManager* mgr) {
    plNetMessage::read(S, mgr);

    fRegionsICareAbout.read(S);
    fRegionsImIn.read(S);
}

void plNetMsgRelevanceRegions::write(hsStream* S, plResManager* mgr) {
    plNetMessage::write(S, mgr);

    fRegionsICareAbout.write(S);
    fRegionsImIn.write(S);
}

void plNetMsgRelevanceRegions::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);

    prc->writeSimpleTag("RegionsICareAbout");
    fRegionsICareAbout.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("RegionsImIn");
    fRegionsImIn.prcWrite(prc);
    prc->closeTag();
}

void plNetMsgRelevanceRegions::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "RegionsICareAbout") {
        if (tag->hasChildren())
            fRegionsICareAbout.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "RegionsImIn") {
        if (tag->hasChildren())
            fRegionsImIn.prcParse(tag->getFirstChild());
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}
