#include "plAvLadderMod.h"

plAvLadderMod::plAvLadderMod()
             : fGoingUp(false), fEnabled(true), fAvatarInBox(false),
               fAvatarMounting(false), fType(kBig), fLoops(0) { }

plAvLadderMod::~plAvLadderMod() { }

IMPLEMENT_CREATABLE(plAvLadderMod, kAvLadderMod, plSingleModifier)

void plAvLadderMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fType = S->readInt();
    fLoops = S->readInt();
    fGoingUp = S->readBool();
    fEnabled = S->readBool();
    fLadderView.read(S);
}

void plAvLadderMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fType);
    S->writeInt(fLoops);
    S->writeBool(fGoingUp);
    S->writeBool(fEnabled);
    fLadderView.write(S);
}

void plAvLadderMod::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("LadderParams");
    prc->writeParam("Type", fType);
    prc->writeParam("Loops", fLoops);
    prc->writeParam("GoingUp", fGoingUp);
    prc->writeParam("Enabled", fEnabled);
    prc->endTag(true);

    prc->writeSimpleTag("LadderView");
    fLadderView.prcWrite(prc);
    prc->closeTag();
}

void plAvLadderMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "LadderParams") {
        fType = tag->getParam("Type", "0").toInt();
        fLoops = tag->getParam("Loops", "0").toInt();
        fGoingUp = tag->getParam("GoingUp", "false").toBool();
        fEnabled = tag->getParam("Enabled", "true").toBool();
    } else if (tag->getName() == "LadderView") {
        if (tag->hasChildren())
            fLadderView.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
