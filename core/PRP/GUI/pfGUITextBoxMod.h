#ifndef _PFGUITEXTBOXMOD_H
#define _PFGUITEXTBOXMOD_H

#include "pfGUIControlMod.h"

DllClass pfGUITextBoxMod : public pfGUIControlMod {
    CREATABLE(pfGUITextBoxMod, kGUITextBoxMod, pfGUIControlMod)

public:
    enum TextBoxFlags { kCenterJustify = kDerivedFlagsStart, kRightJustify };

protected:
    plString fText;
    plWString fLocalizationPath;

public:
    pfGUITextBoxMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getText() const { return fText; }
    plWString getLocalizationPath() const { return fLocalizationPath; }

    void setText(const plString& text) { fText = text; }
    void setLocalizationPath(const plWString& path) { fLocalizationPath = path; }
};

#endif
