#include "plRandomSoundMod.h"

// plRandomSoundModGroup //
plRandomSoundModGroup::plRandomSoundModGroup()
                     : fNumSounds(0), fGroupedIdx(0) { }

plRandomSoundModGroup::~plRandomSoundModGroup() { }

void plRandomSoundModGroup::read(hsStream* S) {
    fNumSounds = S->readShort();
    fGroupedIdx = S->readShort();

    fIndices.setSizeNull(fNumSounds);
    for (size_t i=0; i<fNumSounds; i++)
        fIndices[i] = S->readShort();
}

void plRandomSoundModGroup::write(hsStream* S) {
    S->writeShort(fNumSounds);
    S->writeShort(fGroupedIdx);

    for (size_t i=0; i<fNumSounds; i++)
        S->writeShort(fIndices[i]);
}

void plRandomSoundModGroup::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plRandomSoundModGroup");
    prc->writeParam("GroupedIdx", fGroupedIdx);
    prc->endTag();

    for (size_t i=0; i<fNumSounds; i++) {
        prc->startTag("Sound");
        prc->writeParam("Index", fIndices[i]);
        prc->endTag(true);
    }

    prc->closeTag();
}

void plRandomSoundModGroup::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plRandomSoundModGroup")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fGroupedIdx = tag->getParam("GroupedIdx", "0").toInt();
    fNumSounds = tag->countChildren();
    fIndices.setSizeNull(fNumSounds);
    const pfPrcTag* child = tag->getFirstChild();
    for (size_t i=0; i<fNumSounds; i++) {
        fIndices[i] = child->getParam("Index", "0").toUint();
        child = child->getNextSibling();
    }
}


// plRandomSoundMod //
plRandomSoundMod::plRandomSoundMod() : fNumGroups(0) { }

plRandomSoundMod::~plRandomSoundMod() { }

IMPLEMENT_CREATABLE(plRandomSoundMod, kRandomSoundMod, plRandomCommandMod)

void plRandomSoundMod::read(hsStream* S, plResManager* mgr) {
    plRandomCommandMod::read(S, mgr);

    fNumGroups = S->readShort();
    fGroups.setSize(fNumGroups);
    for (size_t i=0; i<fNumGroups; i++)
        fGroups[i].read(S);
}

void plRandomSoundMod::write(hsStream* S, plResManager* mgr) {
    plRandomCommandMod::write(S, mgr);

    S->writeShort(fNumGroups);
    for (size_t i=0; i<fNumGroups; i++)
        fGroups[i].write(S);
}

void plRandomSoundMod::IPrcWrite(pfPrcHelper* prc) {
    plRandomCommandMod::IPrcWrite(prc);

    prc->writeSimpleTag("Groups");
    for (size_t i=0; i<fNumGroups; i++)
        fGroups[i].prcWrite(prc);
    prc->closeTag();
}

void plRandomSoundMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Groups") {
        fNumGroups = tag->countChildren();
        fGroups.setSize(fNumGroups);
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fNumGroups; i++) {
            fGroups[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plRandomCommandMod::IPrcParse(tag, mgr);
    }
}
