#include "pfGUIEditBoxMod.h"

pfGUIEditBoxMod::pfGUIEditBoxMod()
               : fCursorPos(0), fScrollPos(0), fIgnoreNextKey(false),
                 fEscapedFlag(false), fFirstHalfExitKeyPushed(false),
                 fSpecialCaptureKeyEventMode(false), fSavedKey((plKeyDef)0),
                 fSavedModifiers(0) { }

pfGUIEditBoxMod::~pfGUIEditBoxMod() { }

IMPLEMENT_CREATABLE(pfGUIEditBoxMod, kGUIEditBoxMod, pfGUIControlMod)
