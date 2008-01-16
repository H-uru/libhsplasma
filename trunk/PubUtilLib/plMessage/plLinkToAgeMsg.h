#ifndef _PLLINKTOAGEMSG_H
#define _PLLINKTOAGEMSG_H

#include "../../NucleusLib/pnMessage/plMessage.h"
#include "../plNetCommon/plNetServerSessionInfo.h"

DllClass plLinkToAgeMsg : public plMessage {
protected:
    plAgeLinkStruct fAgeLink;
    plString fLinkInAnimName;
    hsByte fStreamVersion;

public:
    plLinkToAgeMsg();
    virtual ~plLinkToAgeMsg();

    DECLARE_CREATABLE(plLinkToAgeMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
