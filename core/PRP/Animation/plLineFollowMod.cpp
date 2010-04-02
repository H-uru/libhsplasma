#include "plLineFollowMod.h"

/* plLineFollowMod */
plLineFollowMod::plLineFollowMod()
               : fFollowMode(kFollowObject), fFollowFlags(0), fPath(NULL),
                 fOffset(0.0f), fOffsetClamp(0.0f), fSpeedClamp(0.0f) { }

plLineFollowMod::~plLineFollowMod() {
    if (fPath != NULL)
        delete fPath;
}

void plLineFollowMod::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);

    setPath(plAnimPath::Convert(mgr->ReadCreatable(S)));
    fPathParent = mgr->readKey(S);
    fRefObj = mgr->readKey(S);

    fStereizers.setSize(S->readInt());
    for (size_t i=0; i<fStereizers.getSize(); i++)
        fStereizers[i] = mgr->readKey(S);

    unsigned int modeFlags = S->readInt();
    fFollowMode = (FollowMode)(modeFlags & 0xFFFF);
    fFollowFlags = modeFlags >> 16;
    if (fFollowFlags & kOffset)
        fOffset = S->readFloat();
    if (fFollowFlags & kOffsetClamp)
        fOffsetClamp = S->readFloat();
    if (fFollowFlags & kSpeedClamp)
        fSpeedClamp = S->readFloat();
}

void plLineFollowMod::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);

    mgr->WriteCreatable(S, fPath);
    mgr->writeKey(S, fPathParent);
    mgr->writeKey(S, fRefObj);

    S->writeInt(fStereizers.getSize());
    for (size_t i=0; i<fStereizers.getSize(); i++)
        mgr->writeKey(S, fStereizers[i]);

    S->writeInt((fFollowFlags << 16) | fFollowMode);
    if (fFollowFlags & kOffset)
        S->writeFloat(fOffset);
    if (fFollowFlags & kOffsetClamp)
        S->writeFloat(fOffsetClamp);
    if (fFollowFlags & kSpeedClamp)
        S->writeFloat(fSpeedClamp);
}

void plLineFollowMod::IPrcWrite(pfPrcHelper* prc) {
    plMultiModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Path");
      fPath->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Parent");
      fPathParent->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("RefObj");
      fRefObj->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Stereizers");
    for (size_t i=0; i<fStereizers.getSize(); i++)
        fStereizers[i]->prcWrite(prc);
    prc->closeTag();

    prc->startTag("LineFollowParams");
      prc->writeParamHex("FollowFlags", fFollowFlags);
      prc->writeParam("FollowMode", fFollowMode);
      if (fFollowFlags & kOffset)
        prc->writeParam("Offset", fOffset);
      if (fFollowFlags & kOffsetClamp)
        prc->writeParam("OffsetClamp", fOffsetClamp);
      if (fFollowFlags & kSpeedClamp)
        prc->writeParam("SpeedClamp", fSpeedClamp);
    prc->endTag(true);
}

void plLineFollowMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Path") {
        if (tag->hasChildren())
            setPath(plAnimPath::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "Parent") {
        if (tag->hasChildren())
            fPathParent = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "RefObj") {
        if (tag->hasChildren())
            fRefObj = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Stereizers") {
        fStereizers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStereizers.getSize(); i++) {
            fStereizers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "LineFollowParams") {
        fFollowFlags = tag->getParam("FollowFlags", "0").toUint();
        fFollowMode = (FollowMode)tag->getParam("FollowMode", "0").toInt();
        fOffset = tag->getParam("Offset", "0").toFloat();
        fOffsetClamp = tag->getParam("OffsetClamp", "0").toFloat();
        fSpeedClamp = tag->getParam("SpeedClamp", "0").toFloat();
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}

void plLineFollowMod::setPath(plAnimPath* path) {
    if (fPath != NULL)
        delete fPath;
    fPath = path;
}
