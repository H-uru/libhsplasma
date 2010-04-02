#ifndef _PLNETMSGSTREAM_H
#define _PLNETMSGSTREAM_H

#include "plNetMessage.h"
#include "Stream/hsRAMStream.h"
#include "Util/plZlib.h"

DllClass plNetMsgStreamHelper : public plCreatable {
    CREATABLE(plNetMsgStreamHelper, kNetMsgStreamHelper, plCreatable)

public:
    enum CompressionType {
        kCompressionNone, kCompressionFailed, kCompressionZlib,
        kCompressionDont
    };

private:
    unsigned int fUncompressedSize;
    unsigned char fCompressionType;
    unsigned int fStreamLength;
    unsigned char* fStream;

public:
    plNetMsgStreamHelper();
    ~plNetMsgStreamHelper();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

private:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const unsigned char* getStream() const { return fStream; }
    unsigned int getStreamLength() const { return fStreamLength; }
    unsigned int getUncompressedSize() const { return fUncompressedSize; }
    unsigned char getCompressionType() const { return fCompressionType; }

    void setStream(const unsigned char* stream, unsigned int length);
    void setUncompressedSize(unsigned int size) { fUncompressedSize = size; }
    void setCompressionType(unsigned char type) { fCompressionType = type; }

private:
    void decompress(int offset);
};


DllClass plNetMsgStream : public plNetMessage {
    CREATABLE(plNetMsgStream, kNetMsgStream, plNetMessage)

private:
    hsRAMStream fStream;
    unsigned char fCompressionType;

public:
    plNetMsgStream();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

private:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsRAMStream* getStream() { return &fStream; }

    unsigned char getCompressionType() const { return fCompressionType; }
    void setCompressionType(unsigned char type) { fCompressionType = type; }
};

#endif
