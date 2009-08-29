#include "plNetMsgStream.h"

/* plNetMsgStreamHelper */
plNetMsgStreamHelper::plNetMsgStreamHelper()
                    : fUncompressedSize(0), fCompressionType(0),
                      fStreamLength(0), fStream(NULL) { }

plNetMsgStreamHelper::~plNetMsgStreamHelper() {
    if (fStream != NULL)
        delete[] fStream;
}

IMPLEMENT_CREATABLE(plNetMsgStreamHelper, kNetMsgStreamHelper, plCreatable)

void plNetMsgStreamHelper::read(hsStream* S, plResManager* mgr) {
    fUncompressedSize = S->readInt();
    fCompressionType = S->readByte();
    fStreamLength = S->readInt();
    if (fStream != NULL)
        delete[] fStream;
    if (fStreamLength > 0) {
        fStream = new unsigned char[fStreamLength];
        S->read(fStreamLength, fStream);
        Uncompress(2);
    } else {
        fStream = NULL;
    }
}

void plNetMsgStreamHelper::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fUncompressedSize);
    S->writeByte(fCompressionType);
    S->writeInt(fStreamLength);
    S->write(fStreamLength, fStream);
}

void plNetMsgStreamHelper::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Stream");
    prc->writeParam("UncompressedSize", fUncompressedSize);
    prc->writeParam("CompressionType", fCompressionType);
    prc->endTag();
    prc->writeHexStream(fStreamLength, fStream);
    prc->closeTag();
}

void plNetMsgStreamHelper::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Stream") {
        fUncompressedSize = tag->getParam("UncompressedSize", "0").toUint();
        fCompressionType = tag->getParam("CompressionType", "0").toUint();

        if (fStream != NULL)
            delete[] fStream;
        fStreamLength = tag->getContents().getSize();
        fStream = new unsigned char[fStreamLength];
        tag->readHexStream(fStreamLength, fStream);
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

const unsigned char* plNetMsgStreamHelper::getStream() const { return fStream; }
unsigned int plNetMsgStreamHelper::getStreamLength() const { return fStreamLength; }
unsigned int plNetMsgStreamHelper::getUncompressedSize() const { return fUncompressedSize; }
unsigned char plNetMsgStreamHelper::getCompressionType() const { return fCompressionType; }

void plNetMsgStreamHelper::setStream(const unsigned char* stream, unsigned int length) {
    if (fStream != NULL)
        delete[] fStream;
    fStreamLength = length;
    if (fStreamLength != 0) {
        fStream = new unsigned char[fStreamLength];
        memcpy(fStream, stream, fStreamLength);
    } else {
        fStream = NULL;
    }
}

void plNetMsgStreamHelper::setUncompressedSize(unsigned int size) { fUncompressedSize = size; }
void plNetMsgStreamHelper::setCompressionType(unsigned char type) { fCompressionType = type; }

void plNetMsgStreamHelper::Uncompress(int offset) {
	if(fCompressionType == kCompressionZlib) {
    
		if(!plZlib::Uncompress(&fStream, &fStreamLength, fUncompressedSize, offset))
			fCompressionType = kCompressionFailed;
		else fCompressionType = kCompressionNone;
		
	}
}


/* plNetMsgStream */
plNetMsgStream::plNetMsgStream() { }
plNetMsgStream::~plNetMsgStream() { }

IMPLEMENT_CREATABLE(plNetMsgStream, kNetMsgStream, plNetMessage)

void plNetMsgStream::read(hsStream* S, plResManager* mgr) {
    plNetMessage::read(S, mgr);

    plNetMsgStreamHelper helper;
    helper.read(S, mgr);
    fStream.setVer(S->getVer());
    fStream.copyFrom(helper.getStream(), helper.getStreamLength());
    fCompressionType = helper.getCompressionType();
    // TODO: Decompression
}

void plNetMsgStream::write(hsStream* S, plResManager* mgr) {
    plNetMessage::write(S, mgr);

    plNetMsgStreamHelper helper;
    unsigned char* buf = new unsigned char[fStream.size()];
    fStream.copyTo(buf, fStream.size());
    helper.setStream(buf, fStream.size());
    helper.setCompressionType(fCompressionType);
    // TODO: Compression
    helper.write(S, mgr);
    delete[] buf;
}

void plNetMsgStream::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);

    plNetMsgStreamHelper helper;
    unsigned char* buf = new unsigned char[fStream.size()];
    fStream.copyTo(buf, fStream.size());
    helper.setStream(buf, fStream.size());
    helper.prcWrite(prc);
    delete[] buf;
}

void plNetMsgStream::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plNetMsgStreamHelper") {
        plNetMsgStreamHelper helper;
        helper.prcParse(tag, mgr);
        fStream.copyFrom(helper.getStream(), helper.getStreamLength());
        fCompressionType = helper.getCompressionType();
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}

hsStream* plNetMsgStream::getStream() { return &fStream; }

unsigned char plNetMsgStream::getCompressionType() const { return fCompressionType; }
void plNetMsgStream::setCompressionType(unsigned char type) { fCompressionType = type; }
