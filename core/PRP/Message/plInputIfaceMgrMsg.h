#ifndef _PLINPUTIFACEMGRMSG_H
#define _PLINPUTIFACEMGRMSG_H

#include "plMessage.h"

DllClass plInputIfaceMgrMsg : public plMessage {
private:
    unsigned char fCommand;
    unsigned int fPageID;
    plString fAgeName, fAgeFilename, fSpawnPoint;
    plKey fAvKey;

public:
    plInputIfaceMgrMsg();
    virtual ~plInputIfaceMgrMsg();

    DECLARE_CREATABLE(plInputIfaceMgrMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
