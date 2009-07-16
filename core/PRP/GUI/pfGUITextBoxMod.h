#ifndef _PFGUITEXTBOXMOD_H
#define _PFGUITEXTBOXMOD_H

#include "pfGUIControlMod.h"

DllClass pfGUITextBoxMod : public pfGUIControlMod {
public:
    enum TextBoxFlags { kCenterJustify = kDerivedFlagsStart, kRightJustify };

protected:
    plString fText;
    plWString fLocalizationPath;

public:
    pfGUITextBoxMod();
    virtual ~pfGUITextBoxMod();

    DECLARE_CREATABLE(pfGUITextBoxMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const plString& getText() const;
    const plWString& getLocalizationPath() const;

    void setText(const plString& text);
    void setLocalizationPath(const plWString& path);
};

#endif
