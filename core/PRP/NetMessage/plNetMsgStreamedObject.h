#ifndef _PLNETMSGSTREAMEDOBJECT_H
#define _PLNETMSGSTREAMEDOBJECT_H

#include "plNetMsgStream.h"
#include "plNetMsgObject.h"

DllClass plNetMsgStreamedObject : public plNetMsgObject {
    CREATABLE(plNetMsgStreamedObject, kNetMsgStreamedObject, plNetMsgObject)

private:
    hsRAMStream fStream;
    unsigned char fCompressionType;

public:
    plNetMsgStreamedObject();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsRAMStream* getStream() { return &fStream; }

    unsigned char getCompressionType() const { return fCompressionType; }
    void setCompressionType(unsigned char type) { fCompressionType = type; }
};

#endif
