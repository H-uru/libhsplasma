#include "plArmatureBrain.h"

/* plArmatureBrain */
plArmatureBrain::plArmatureBrain() { }
plArmatureBrain::~plArmatureBrain() { }

IMPLEMENT_CREATABLE(plArmatureBrain, kArmatureBrain, plCreatable)

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
plAvBrainHuman::~plAvBrainHuman() { }

IMPLEMENT_CREATABLE(plAvBrainHuman, kAvBrainHuman, plArmatureBrain)

void plAvBrainHuman::read(hsStream* S, plResManager* mgr) {
    plArmatureBrain::read(S, mgr);

    if (S->getVer() == pvLive)
        fIsCustomAvatar = S->readBool();
    else
        fIsCustomAvatar = false;
}

void plAvBrainHuman::write(hsStream* S, plResManager* mgr) {
    plArmatureBrain::write(S, mgr);

    if (S->getVer() == pvLive)
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

bool plAvBrainHuman::isCustomAvatar() const { return fIsCustomAvatar; }
void plAvBrainHuman::setIsCustomAvatar(bool value) { fIsCustomAvatar = value; }


/* plAvBrainClimb */
IMPLEMENT_CREATABLE(plAvBrainClimb, kAvBrainClimb, plArmatureBrain)


/* plAvBrainCritter */
IMPLEMENT_CREATABLE(plAvBrainCritter, kAvBrainCritter, plArmatureBrain)


/* plAvBrainDrive */
IMPLEMENT_CREATABLE(plAvBrainDrive, kAvBrainDrive, plArmatureBrain)


/* plAvBrainPirahna */
IMPLEMENT_CREATABLE(plAvBrainPirahna, kAvBrainPirahna, plArmatureBrain)


/* plAvBrainQuab */
IMPLEMENT_CREATABLE(plAvBrainQuab, kAvBrainQuab, plArmatureBrain)


/* plAvBrainRideAnimatedPhysical */
IMPLEMENT_CREATABLE(plAvBrainRideAnimatedPhysical, kAvBrainRideAnimatedPhysical, plArmatureBrain)


/* plAvBrainSwim */
IMPLEMENT_CREATABLE(plAvBrainSwim, kAvBrainSwim, plArmatureBrain)
