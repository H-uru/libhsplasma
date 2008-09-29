#ifndef _PFGUICONTROLMOD_H
#define _PFGUICONTROLMOD_H

#include "PRP/Modifier/plModifier.h"
#include "Sys/hsColor.h"
#include "Math/hsGeometry3.h"
#include "PRP/Region/hsBounds.h"
#include "Math/hsMatrix44.h"
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
    void prcParse(const pfPrcTag* tag);

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
    bool fVisible;
    hsBounds3 fBounds, fInitialBounds;
    pfGUICtrlProcWriteableObject* fHandler;
    plKey fDynTextMap, fDynTextLayer;
    pfGUIColorScheme* fColorScheme;
    hsTArray<int> fSoundIndices;
    plKey fProxy, fSkin;

public:
    pfGUIControlMod();
    virtual ~pfGUIControlMod();

    DECLARE_CREATABLE(pfGUIControlMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
