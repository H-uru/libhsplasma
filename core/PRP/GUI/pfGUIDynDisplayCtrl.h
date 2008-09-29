#ifndef _PFGUIDYNDISPLAYCTRL_H
#define _PFGUIDYNDISPLAYCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIDynDisplayCtrl : public pfGUIControlMod {
protected:
    hsTArray<plKey> fTextMaps, fLayers, fMaterials;

public:
    pfGUIDynDisplayCtrl();
    virtual ~pfGUIDynDisplayCtrl();

    DECLARE_CREATABLE(pfGUIDynDisplayCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
