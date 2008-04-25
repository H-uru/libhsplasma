#include "plLineFollowMod.h"
#include <cmath>

/* plLineFollowMod */
plLineFollowMod::plLineFollowMod() : fPath(NULL) { }

plLineFollowMod::~plLineFollowMod() {
    if (fPath != NULL)
        delete fPath;
}

IMPLEMENT_CREATABLE(plLineFollowMod, kLineFollowMod, plMultiModifier)

void plLineFollowMod::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);

    fPath = plAnimPath::Convert(mgr->ReadCreatable(S));
    fPathParent = mgr->readKey(S);
    fRefObj = mgr->readKey(S);

    unsigned int count = S->readInt();
    fStereizers.setSize(count);
    for (unsigned int i=0; i<count; i++)
        fStereizers[i] = mgr->readKey(S);

    unsigned int modeFlags = S->readInt();
    //IUnRegister();
    fFollowMode = (FollowMode)(modeFlags & 0xFFFF);
    //IRegister();
    fFollowFlags = modeFlags >> 16;
    if (fFollowFlags & kOffset)
        fOffset = S->readFloat();
    if (fFollowFlags & kOffsetAng)
        fTanOffset = tan(fOffset);
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
    for (unsigned int i=0; i<fStereizers.getSize(); i++)
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

    fPath->prcWrite(prc);
    prc->writeSimpleTag("Parent");
      fPathParent->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("RefObj");
      fRefObj->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Stereizers");
    for (unsigned int i=0; i<fStereizers.getSize(); i++)
        fStereizers[i]->prcWrite(prc);
    prc->closeTag();

    prc->startTag("Parameters");
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


/* plRailCameraMod */
plRailCameraMod::plRailCameraMod() { }
plRailCameraMod::~plRailCameraMod() { }

IMPLEMENT_CREATABLE(plRailCameraMod, kRailCameraMod, plLineFollowMod)
