#ifndef _PLNETMSGPLAYERPAGE_H
#define _PLNETMSGPLAYERPAGE_H

#include "plNetMessage.h"
#include "PRP/KeyedObject/plUoid.h"

DllClass plNetMsgPlayerPage : public plNetMessage {
    CREATABLE(plNetMsgPlayerPage, kNetMsgPlayerPage, plNetMessage)

private:
    unsigned char fUnload;
    plUoid fUoid;

public:
    plNetMsgPlayerPage();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

private:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned char getUnload() const { return fUnload; }
    plUoid getUoid() const { return fUoid; }

    void setUnload(unsigned char unload) { fUnload = unload; }
    void setUoid(const plUoid& uoid) { fUoid = uoid; }
};

#endif
