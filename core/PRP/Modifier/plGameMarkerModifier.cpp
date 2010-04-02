#include "plGameMarkerModifier.h"

plGameMarkerModifier::plGameMarkerModifier()
                    : fPlaceSoundIdx(0), fHitSoundIdx(0) { }

void plGameMarkerModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fGreenAnimKey = mgr->readKey(S);
    fRedAnimKey = mgr->readKey(S);
    fOpenAnimKey = mgr->readKey(S);
    fBounceAnimKey = mgr->readKey(S);
    fPlaceSoundIdx = S->readShort();
    fHitSoundIdx = S->readShort();
}

void plGameMarkerModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    mgr->writeKey(S, fGreenAnimKey);
    mgr->writeKey(S, fRedAnimKey);
    mgr->writeKey(S, fOpenAnimKey);
    mgr->writeKey(S, fBounceAnimKey);
    S->writeShort(fPlaceSoundIdx);
    S->writeShort(fHitSoundIdx);
}

void plGameMarkerModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("GreenAnim");
    fGreenAnimKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("RedAnim");
    fRedAnimKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("OpenAnim");
    fOpenAnimKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("BounceAnim");
    fBounceAnimKey->prcWrite(prc);
    prc->closeTag();

    prc->startTag("SoundIndices");
    prc->writeParam("Place", fPlaceSoundIdx);
    prc->writeParam("Hit", fHitSoundIdx);
    prc->endTag(true);
}

void plGameMarkerModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "GreenAnim") {
        if (tag->hasChildren())
            fGreenAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "RedAnim") {
        if (tag->hasChildren())
            fRedAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "OpenAnim") {
        if (tag->hasChildren())
            fOpenAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "BounceAnim") {
        if (tag->hasChildren())
            fBounceAnimKey = mgr->prcParseKey(tag);
    } else if (tag->getName() == "SoundIndices") {
        fPlaceSoundIdx = tag->getParam("Place", "0").toUint();
        fHitSoundIdx = tag->getParam("Hit", "0").toUint();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
