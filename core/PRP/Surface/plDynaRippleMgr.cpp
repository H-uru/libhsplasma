#include "plDynaRippleMgr.h"

/* plDynaRippleMgr */
void plDynaRippleMgr::read(hsStream* S, plResManager* mgr) {
    plDynaDecalMgr::read(S, mgr);
    fInitUVW.read(S);
    fFinalUVW.read(S);
}

void plDynaRippleMgr::write(hsStream* S, plResManager* mgr) {
    plDynaDecalMgr::write(S, mgr);
    fInitUVW.write(S);
    fFinalUVW.write(S);
}

void plDynaRippleMgr::IPrcWrite(pfPrcHelper* prc) {
    plDynaDecalMgr::IPrcWrite(prc);

    prc->writeSimpleTag("InitUVW");
    fInitUVW.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("FinalUVW");
    fFinalUVW.prcWrite(prc);
    prc->closeTag();
}

void plDynaRippleMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "InitUVW") {
        if (tag->hasChildren())
            fInitUVW.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "FinalUVW") {
        if (tag->hasChildren())
            fFinalUVW.prcParse(tag->getFirstChild());
    } else {
        plDynaDecalMgr::IPrcParse(tag, mgr);
    }
}


/* plDynaRippleVSMgr */
void plDynaRippleVSMgr::read(hsStream* S, plResManager* mgr) {
    plDynaRippleMgr::read(S, mgr);
    fWaveSetBase = mgr->readKey(S);
}

void plDynaRippleVSMgr::write(hsStream* S, plResManager* mgr) {
    plDynaRippleMgr::write(S, mgr);
    mgr->writeKey(S, fWaveSetBase);
}

void plDynaRippleVSMgr::IPrcWrite(pfPrcHelper* prc) {
    plDynaRippleMgr::IPrcWrite(prc);

    prc->writeSimpleTag("WaveSet");
    fWaveSetBase->prcWrite(prc);
    prc->closeTag();
}

void plDynaRippleVSMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "WaveSet") {
        if (tag->hasChildren())
            fWaveSetBase = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plDynaRippleMgr::IPrcParse(tag, mgr);
    }
}


/* plDynaTorpedoVSMgr */
void plDynaTorpedoVSMgr::read(hsStream* S, plResManager* mgr) {
    plDynaTorpedoMgr::read(S, mgr);
    fWaveSetBase = mgr->readKey(S);
}

void plDynaTorpedoVSMgr::write(hsStream* S, plResManager* mgr) {
    plDynaTorpedoMgr::write(S, mgr);
    mgr->writeKey(S, fWaveSetBase);
}

void plDynaTorpedoVSMgr::IPrcWrite(pfPrcHelper* prc) {
    plDynaTorpedoMgr::IPrcWrite(prc);

    prc->writeSimpleTag("WaveSet");
    fWaveSetBase->prcWrite(prc);
    prc->closeTag();
}

void plDynaTorpedoVSMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "WaveSet") {
        if (tag->hasChildren())
            fWaveSetBase = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plDynaRippleMgr::IPrcParse(tag, mgr);
    }
}


/* plDynaWakeMgr */
plDynaWakeMgr::plDynaWakeMgr() : fAnimPath(NULL), fAnimWgt(0.0f), fVelWgt(0.0f) { }

plDynaWakeMgr::~plDynaWakeMgr() {
    delete fAnimPath;
}

void plDynaWakeMgr::read(hsStream* S, plResManager* mgr) {
    plDynaRippleMgr::read(S, mgr);

    fDefaultDir.read(S);
    setAnimPath(plAnimPath::Convert(mgr->ReadCreatable(S)));
    fAnimWgt = S->readFloat();
    fVelWgt = S->readFloat();
}

void plDynaWakeMgr::write(hsStream* S, plResManager* mgr) {
    plDynaRippleMgr::write(S, mgr);

    fDefaultDir.write(S);
    mgr->WriteCreatable(S, fAnimPath);
    S->writeFloat(fAnimWgt);
    S->writeFloat(fVelWgt);
}

void plDynaWakeMgr::IPrcWrite(pfPrcHelper* prc) {
    plDynaRippleMgr::IPrcWrite(prc);

    prc->writeSimpleTag("DefaultDir");
    fDefaultDir.prcWrite(prc);
    prc->closeTag();

    prc->startTag("DynaWakeMgrParams");
    prc->writeParam("AnimWeight", fAnimWgt);
    prc->writeParam("VelWeight", fVelWgt);
    prc->endTag(true);

    if (fAnimPath != NULL) {
        fAnimPath->prcWrite(prc);
    } else {
        prc->startTag("plAnimPath");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plDynaWakeMgr::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DefaultDir") {
        if (tag->hasChildren())
            fDefaultDir.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "DynaWakeMgrParams") {
        fAnimWgt = tag->getParam("AnimWeight", "0").toFloat();
        fVelWgt = tag->getParam("VelWeight", "0").toFloat();
    } else if (tag->getName() == "plAnimPath") {
        if (tag->getParam("NULL", "false").toBool()) {
            setAnimPath(NULL);
        } else {
            if (tag->hasChildren())
                setAnimPath(plAnimPath::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
        }
    } else {
        plDynaRippleMgr::IPrcParse(tag, mgr);
    }
}

void plDynaWakeMgr::setAnimPath(plAnimPath* path) {
    delete fAnimPath;
    fAnimPath = path;
}
