#ifndef _PFGUICONTROLMOD_H
#define _PFGUICONTROLMOD_H

#include "../../NucleusLib/pnModifier/plModifier.h"
#include "../../CoreLib/hsColor.h"
#include "../../CoreLib/hsGeometry3.h"
#include "../../CoreLib/hsBounds.h"
#include "../../CoreLib/hsMatrix44.h"
#include "pfGUIControlHandlers.h"

DllClass pfGUIColorScheme {
protected:
    hsColorRGBA fForeColor, fBackColor, fSelForeColor, fSelBackColor;
    int fTransparent;
    plString fFontFace;
    unsigned char fFontSize, fFontFlags;

public:
    pfGUIColorScheme();
    ~pfGUIColorScheme();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);

private:
    void IReset();
};

DllClass pfGUIControlMod : public plSingleModifier {
public:
    enum {
        kWantsInterest, kInheritProcFromDlg, kIntangible, kXparentBgnd,
        kScaleTextWithResolution, kTakesSpecialKeys, kHasProxy,
        kBetterHitTesting, kDerivedFlagsStart = 0x20
    };

protected:
    unsigned int fTagID;
    bool fEnabled, fFocused, fVisible, fInteresting, fNotifyOnInteresting;
    class pfGUIDialogMod* fDialog;
    hsBounds3 fBounds, fInitialBounds;
    float fScreenMinZ;
    hsPoint3 fScreenCenter;
    bool fBoundsValid, fCenterValid;
    hsMatrix44 fXformMatrix;
    pfGUICtrlProcWriteableObject* fHandler;
    //pfGUIDropTargetProc* fDropTargetHandler;
    plKey fDynTextMap, fDynTextLayer;
    pfGUIColorScheme* fColorScheme;
    plKey fProxy;
    hsTArray<hsPoint3> fBoundsPoints;
    hsTArray<int> fSoundIndices;
    plKey fSkin;

public:
    pfGUIControlMod();
    virtual ~pfGUIControlMod();

    DECLARE_CREATABLE(pfGUIControlMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
