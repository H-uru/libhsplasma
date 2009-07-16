#ifndef _PFGUIMULTILINEEDITCTRL_H
#define _PFGUIMULTILINEEDITCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIMultiLineEditCtrl : public pfGUIControlMod {
protected:
    plKey fScrollCtrl;

public:
    pfGUIMultiLineEditCtrl();
    virtual ~pfGUIMultiLineEditCtrl();

    DECLARE_CREATABLE(pfGUIMultiLineEditCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getScrollCtrl() const;
    void setScrollCtrl(plKey ctrl);
};

#endif
