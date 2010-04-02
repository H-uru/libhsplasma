#include "plNetMsgStreamedObject.h"

/* plNetMsgStreamedObject */
plNetMsgStreamedObject::plNetMsgStreamedObject() : fCompressionType(0) { }

void plNetMsgStreamedObject::read(hsStream* S, plResManager* mgr) {
    plNetMsgObject::read(S, mgr);

    plNetMsgStreamHelper helper;
    helper.read(S, mgr);
    fStream.setVer(S->getVer());
    fStream.copyFrom(helper.getStream(), helper.getStreamLength());
    fCompressionType = helper.getCompressionType();
    // TODO: Decompression
}

void plNetMsgStreamedObject::write(hsStream* S, plResManager* mgr) {
    plNetMsgObject::write(S, mgr);

    plNetMsgStreamHelper helper;
    unsigned char* buf = new unsigned char[fStream.size()];
    fStream.copyTo(buf, fStream.size());
    helper.setStream(buf, fStream.size());
    helper.setCompressionType(fCompressionType);
    // TODO: Compression
    helper.write(S, mgr);
    delete[] buf;
}

void plNetMsgStreamedObject::IPrcWrite(pfPrcHelper* prc) {
    plNetMsgObject::IPrcWrite(prc);

    plNetMsgStreamHelper helper;
    unsigned char* buf = new unsigned char[fStream.size()];
    fStream.copyTo(buf, fStream.size());
    helper.setStream(buf, fStream.size());
    helper.prcWrite(prc);
    delete[] buf;
}

void plNetMsgStreamedObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "plNetMsgStreamHelper") {
        plNetMsgStreamHelper helper;
        helper.prcParse(tag, mgr);
        fStream.copyFrom(helper.getStream(), helper.getStreamLength());
        fCompressionType = helper.getCompressionType();
    } else {
        plNetMsgObject::IPrcParse(tag, mgr);
    }
}
