#ifndef _PLNETMSGSTREAM_H
#define _PLNETMSGSTREAM_H

#include "plNetMessage.h"
#include "Stream/hsRAMStream.h"

DllClass plNetMsgStreamHelper : public plCreatable {
private:
    unsigned int fUncompressedSize;
    unsigned char fCompressionType;
    unsigned int fStreamLength;
    unsigned char* fStream;

public:
    plNetMsgStreamHelper();
    ~plNetMsgStreamHelper();

    DECLARE_CREATABLE(plNetMsgStreamHelper)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

private:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const unsigned char* getStream() const;
    unsigned int getStreamLength() const;
    unsigned int getUncompressedSize() const;
    unsigned char getCompressionType() const;

    void setStream(const unsigned char* stream, unsigned int length);
    void setUncompressedSize(unsigned int size);
    void setCompressionType(unsigned char type);
};

DllClass plNetMsgStream : public plNetMessage {
private:
    hsRAMStream fStream;
    unsigned char fCompressionType;

public:
    plNetMsgStream();
    ~plNetMsgStream();

    DECLARE_CREATABLE(plNetMsgStream)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

private:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsStream* getStream();

    unsigned char getCompressionType() const;
    void setCompressionType(unsigned char type);
};

#endif
