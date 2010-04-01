#ifndef _PLNETMSGOBJECT_H
#define _PLNETMSGOBJECT_H

#include "plNetMessage.h"
#include "PRP/KeyedObject/plUoid.h"

DllClass plNetMsgObjectHelper : public plCreatable {
private:
    plUoid fUoid;

public:
    plNetMsgObjectHelper();
    ~plNetMsgObjectHelper();

    DECLARE_CREATABLE(plNetMsgObjectHelper)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    //accessors
    plUoid getUoid() const;

    //mutators
    void setUoid(plUoid Uoid);
};

DllClass plNetMsgObject : public plNetMessage {
private:
    plNetMsgObjectHelper fHelper;

public:
    plNetMsgObject();
    ~plNetMsgObject();

    DECLARE_CREATABLE(plNetMsgObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plNetMsgObjectHelper getHelper() const;

    void setHelper(plNetMsgObjectHelper Helper);
};

#endif
