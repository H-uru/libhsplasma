#include "plArmatureBrain.h"

/* plArmatureBrain */
void plArmatureBrain::read(hsStream* S, plResManager* mgr) {
    // Yay for uselessness
    S->readInt();
    if (S->readBool())
        mgr->readKey(S);
    S->readInt();
    S->readFloat();
    S->readDouble();
}

void plArmatureBrain::write(hsStream* S, plResManager* mgr) {
    S->writeInt(0);
    S->writeBool(false);
    S->writeInt(0);
    S->writeFloat(0.0f);
    S->writeDouble(0.0);
}

void plArmatureBrain::IPrcWrite(pfPrcHelper* prc) { }

void plArmatureBrain::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    plCreatable::IPrcParse(tag, mgr);
}


/* plAvBrainHuman */
plAvBrainHuman::plAvBrainHuman() : fIsCustomAvatar(false) { }

void plAvBrainHuman::read(hsStream* S, plResManager* mgr) {
    plArmatureBrain::read(S, mgr);

    if (S->getVer() == pvLive || S->getVer() == pvUniversal)
        fIsCustomAvatar = S->readBool();
    else
        fIsCustomAvatar = false;
}

void plAvBrainHuman::write(hsStream* S, plResManager* mgr) {
    plArmatureBrain::write(S, mgr);

    if (S->getVer() == pvLive || S->getVer() == pvUniversal)
        S->writeBool(fIsCustomAvatar);
}

void plAvBrainHuman::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("HumanParams");
    prc->writeParam("IsCustomAvatar", fIsCustomAvatar);
    prc->endTag(true);
}

void plAvBrainHuman::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "HumanParams") {
        fIsCustomAvatar = tag->getParam("IsCustomAvatar", "false").toBool();
    } else {
        plArmatureBrain::IPrcParse(tag, mgr);
    }
}
