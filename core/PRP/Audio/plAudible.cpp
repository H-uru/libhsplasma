#include "plAudible.h"

/* plWinAudible */
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
