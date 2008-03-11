#include "plSpanInstance.h"

/* plSpanEncoding */
plSpanEncoding::plSpanEncoding() : fCode(0), fPosScale(0.0f) { }
plSpanEncoding::~plSpanEncoding() { }

void plSpanEncoding::read(hsStream* S) {
    fCode = S->readByte();
    fPosScale = S->readFloat();
}

void plSpanEncoding::write(hsStream* S) {
    S->writeByte(fCode);
    S->writeFloat(fPosScale);
}

void plSpanEncoding::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plSpanEncoding");
    prc->writeParam("Code", fCode);
    prc->writeParam("PosScale", fPosScale);
    prc->endTag(true);
}

unsigned int plSpanEncoding::getCode() const { return fCode; }
float plSpanEncoding::getPosScale() const { return fPosScale; }


/* plSpanInstance */
plSpanInstance::plSpanInstance() : fPosDelta(NULL), fCol(NULL) { }

plSpanInstance::~plSpanInstance() {
    if (fPosDelta != NULL)
        delete[] fPosDelta;
    if (fCol != NULL)
        delete[] fCol;
}

void plSpanInstance::read(hsStream* S, const plSpanEncoding& encoding,
                          unsigned int numVerts) {
    S->read(sizeof(fL2W), fL2W);

    if (fPosDelta != NULL)
        delete[] fPosDelta;
    if (fCol != NULL)
        delete[] fCol;

    unsigned int posStride = CalcPosStride(encoding);
    if (posStride != 0) {
        fPosDelta = new unsigned char[posStride * numVerts];
        S->read(posStride * numVerts, fPosDelta);
    } else {
        fPosDelta = NULL;
    }
    unsigned int colStride = CalcColStride(encoding);
    if (colStride != 0) {
        fCol = new unsigned char[colStride * numVerts];
        S->read(colStride * numVerts, fCol);
    } else {
        fCol = NULL;
    }
}

void plSpanInstance::write(hsStream* S, const plSpanEncoding& encoding,
                           unsigned int numVerts) {
    S->write(sizeof(fL2W), fL2W);
    if (fPosDelta != NULL)
        S->write(CalcPosStride(encoding) * numVerts, fPosDelta);
    if (fCol != NULL)
        S->write(CalcColStride(encoding) * numVerts, fCol);
}

void plSpanInstance::prcWrite(pfPrcHelper* prc, const plSpanEncoding& encoding,
                              unsigned int numVerts) {
    prc->writeSimpleTag("plSpanInstance");

    prc->writeTagNoBreak("Local2World");
    prc->getStream()->writeStr(
        plString::Format("[ %.04f %.04f %.04f %.04f "
                         "; %.04f %.04f %.04f %.04f "
                         "; %.04f %.04f %.04f %.04f ]",
                         fL2W[0][0], fL2W[0][1], fL2W[0][2], fL2W[0][3],
                         fL2W[1][0], fL2W[1][1], fL2W[1][2], fL2W[1][3],
                         fL2W[2][0], fL2W[2][1], fL2W[2][2], fL2W[2][3]));
    prc->closeTagNoBreak();

    prc->writeSimpleTag("PosDeltas");
    prc->writeComment("Decoder Incomplete");
    prc->closeTag();

    prc->writeSimpleTag("Colors");
    prc->writeComment("Decoder Incomplete");
    prc->closeTag();

    prc->closeTag();
}

unsigned int plSpanInstance::CalcPosStride(const plSpanEncoding& encoding) {
    switch (encoding.getCode() & plSpanEncoding::kPosMask) {
    case plSpanEncoding::kPos888:
        return 3;
    case plSpanEncoding::kPos161616:
        return 6;
    case plSpanEncoding::kPos101010:
        return 4;
    case plSpanEncoding::kPos008:
        return 1;
    default:
        return 0;
    }
}

unsigned int plSpanInstance::CalcColStride(const plSpanEncoding& encoding) {
    return 0;   // Because of a bug in Cyan's code...

    switch (encoding.getCode() & plSpanEncoding::kColMask) {
    case plSpanEncoding::kColA8:
        return 1;
    case plSpanEncoding::kColI8:
        return 1;
    case plSpanEncoding::kColAI88:
        return 2;
    case plSpanEncoding::kColRGB888:
        return 3;
    case plSpanEncoding::kColARGB8888:
        return 4;
    default:
        return 0;
    }
}
