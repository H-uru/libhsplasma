#ifndef _PLLINKTOAGEMSG_H
#define _PLLINKTOAGEMSG_H

#include "plMessage.h"
#include "PRP/Misc/plAgeLinkInfo.h"

DllClass plLinkToAgeMsg : public plMessage {
protected:
    plAgeLinkStruct fAgeLink;
    plAgeLinkEffects fLinkEffects;
    hsByte fStreamVersion, fEoaUnknown;

public:
    plLinkToAgeMsg();
    virtual ~plLinkToAgeMsg();

    DECLARE_CREATABLE(plLinkToAgeMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
