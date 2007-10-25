#include "pfGUIMultiLineEditCtrl.h"

/* pfMLScrollProc */
pfMLScrollProc::pfMLScrollProc(pfGUIMultiLineEditCtrl* parent)
              : fParent(parent) { }

void pfMLScrollProc::DoSomething(pfGUIControlMod* ctrl) {
    //TODO: Scroll...
}

/* pfGUIMultiLineEditCtrl */
pfGUIMultiLineEditCtrl::pfGUIMultiLineEditCtrl()
                      : fLineHeight(0), fCurrCursorX(0), fCurrCursorY(0),
                        fIgnoreNextKey(false), fReadyToRender(false),
                        fLockCount(0), fCalcedFontSize(0), fLastKeyModifiers(0),
                        fLastKeyPressed(0), fLastDeadKey(0), fScrollProc(NULL),
                        fScrollPos(0), fBufferLimit(-1), fNextCtrl(NULL),
                        fPrevCtrl(NULL), fEventProc(NULL), fFontSize(0),
                        fFontStyle(0), fFontFlagsSet(0), fTopMargin(0),
                        fLeftMargin(0), fBottomMargin(0), fRightMargin(0) { }

pfGUIMultiLineEditCtrl::~pfGUIMultiLineEditCtrl() { }

IMPLEMENT_CREATABLE(pfGUIMultiLineEditCtrl, kGUIMultiLineEditCtrl, pfGUIControlMod)

void pfGUIMultiLineEditCtrl::read(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::read(S, mgr);

    if (S->readBool()) {
        fScrollProc = new pfMLScrollProc(this);
        fScrollCtrl = mgr->readKey(S);
    }
}

void pfGUIMultiLineEditCtrl::write(hsStream* S, plResManager* mgr) {
    pfGUIControlMod::write(S, mgr);

    if (fScrollCtrl.Exists()) {
        S->writeBool(true);
        mgr->writeKey(S, fScrollCtrl);
    } else {
        S->writeBool(false);
    }
}

void pfGUIMultiLineEditCtrl::prcWrite(pfPrcHelper* prc) {
    pfGUIControlMod::prcWrite(prc);

    prc->writeSimpleTag("ScrollCtrl");
    fScrollCtrl->prcWrite(prc);
    prc->closeTag();
}
