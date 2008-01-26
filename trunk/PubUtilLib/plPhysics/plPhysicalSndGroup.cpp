#include "plPhysicalSndGroup.h"

plPhysicalSndGroup::plPhysicalSndGroup() : fGroup(kNone), fCurrSlideSnd(0) { }
plPhysicalSndGroup::~plPhysicalSndGroup() { }

IMPLEMENT_CREATABLE(plPhysicalSndGroup, kPhysicalSndGroup, hsKeyedObject)

void plPhysicalSndGroup::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fGroup = S->readInt();
    fImpactSounds.setSize(S->readInt());
    for (size_t i=0; i<fImpactSounds.getSize(); i++)
        fImpactSounds[i] = mgr->readKey(S);
    fSlideSounds.setSize(S->readInt());
    for (size_t i=0; i<fSlideSounds.getSize(); i++)
        fSlideSounds[i] = mgr->readKey(S);
}

void plPhysicalSndGroup::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(fGroup);
    S->writeInt(fImpactSounds.getSize());
    for (size_t i=0; i<fImpactSounds.getSize(); i++)
        mgr->writeKey(S, fImpactSounds[i]);
    S->writeInt(fSlideSounds.getSize());
    for (size_t i=0; i<fSlideSounds.getSize(); i++)
        mgr->writeKey(S, fSlideSounds[i]);
}

void plPhysicalSndGroup::prcWrite(pfPrcHelper* prc) {
    hsKeyedObject::prcWrite(prc);

    prc->startTag("SoundGroupParams");
    prc->writeParam("Group", fGroup);
    prc->endTag(true);

    prc->writeSimpleTag("ImpactSounds");
    for (size_t i=0; i<fImpactSounds.getSize(); i++)
        fImpactSounds[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SlideSounds");
    for (size_t i=0; i<fSlideSounds.getSize(); i++)
        fSlideSounds[i]->prcWrite(prc);
    prc->closeTag();
}
