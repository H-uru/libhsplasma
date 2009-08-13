#ifndef _PLNETMSGSTREAMEDOBJECT_H
#define _PLNETMSGSTREAMEDOBJECT_H

#include "plNetMsgStream.h"
#include "plNetMsgObject.h"

DllClass plNetMsgStreamedObject : public plNetMsgObject {
private:
    hsRAMStream fStream;
    unsigned char fCompressionType;

public:
    plNetMsgStreamedObject();
    ~plNetMsgStreamedObject();

    DECLARE_CREATABLE(plNetMsgStreamedObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsStream* getStream();

    unsigned char getCompressionType() const;
    void setCompressionType(unsigned char type);
};

#endif
