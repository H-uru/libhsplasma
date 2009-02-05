#include "plAudible.h"

/* plAudible */
plAudible::plAudible() { }
plAudible::~plAudible() { }

IMPLEMENT_CREATABLE(plAudible, kAudible, hsKeyedObject)


/* plAudibleNull */
plAudibleNull::plAudibleNull() { }
plAudibleNull::~plAudibleNull() { }

IMPLEMENT_CREATABLE(plAudibleNull, kAudibleNull, plAudible)


/* plWinAudible */
plWinAudible::plWinAudible() { }
plWinAudible::~plWinAudible() { }

IMPLEMENT_CREATABLE(plWinAudible, kWinAudible, plAudible)

void plWinAudible::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fSoundObjs.setSize(S->readInt());
    for (size_t i=0; i<fSoundObjs.getSize(); i++)
        fSoundObjs[i] = mgr->readKey(S);
    fSceneNode = mgr->readKey(S);
}

void plWinAudible::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(fSoundObjs.getSize());
    for (size_t i=0; i<fSoundObjs.getSize(); i++)
        mgr->writeKey(S, fSoundObjs[i]);
    mgr->writeKey(S, fSceneNode);
}

void plWinAudible::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("SoundObjects");
    for (size_t i=0; i<fSoundObjs.getSize(); i++)
        fSoundObjs[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SceneNode");
    fSceneNode->prcWrite(prc);
    prc->closeTag();
}

void plWinAudible::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SoundObjects") {
        fSoundObjs.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSoundObjs.getSize(); i++) {
            fSoundObjs[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

size_t plWinAudible::getNumSounds() const { return fSoundObjs.getSize(); }
plKey plWinAudible::getSound(size_t idx) const { return fSoundObjs[idx]; }
void plWinAudible::addSound(plKey sound) { fSoundObjs.append(sound); }
void plWinAudible::delSound(size_t idx) { fSoundObjs.remove(idx); }
void plWinAudible::clearSounds() { fSoundObjs.clear(); }

plKey plWinAudible::getSceneNode() const { return fSceneNode; }
void plWinAudible::setSceneNode(plKey node) { fSceneNode = node; }


/* pl2WayWinAudible */
pl2WayWinAudible::pl2WayWinAudible() { }
pl2WayWinAudible::~pl2WayWinAudible() { }

IMPLEMENT_CREATABLE(pl2WayWinAudible, k2WayWinAudible, plWinAudible)
