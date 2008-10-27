#include "plSpanInstance.h"

/* plSpanEncoding */
plSpanEncoding::plSpanEncoding() : fCode(0), fPosScale(0.0f) { }
plSpanEncoding::plSpanEncoding(const plSpanEncoding& init)
              : fCode(init.fCode), fPosScale(init.fPosScale) { }
plSpanEncoding::~plSpanEncoding() { }

plSpanEncoding& plSpanEncoding::operator=(const plSpanEncoding& init) {
    fCode = init.fCode;
    fPosScale = init.fPosScale;
    return *this;
}

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

void plSpanEncoding::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plSpanEncoding")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fCode = tag->getParam("Code", "0").toUint();
    fPosScale = tag->getParam("PosScale", "0").toFloat();
}

unsigned int plSpanEncoding::getCode() const { return fCode; }
float plSpanEncoding::getPosScale() const { return fPosScale; }

void plSpanEncoding::setCode(unsigned int code) { fCode = code; }
void plSpanEncoding::setPosScale(float scale) { fPosScale = scale; }


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
    fEncoding = encoding;
    fNumVerts = numVerts;

    S->read(sizeof(fL2W), fL2W);

    if (fPosDelta != NULL)
        delete[] fPosDelta;
    if (fCol != NULL)
        delete[] fCol;

    unsigned int posStride = CalcPosStride(fEncoding);
    if (posStride != 0) {
        fPosDelta = new unsigned char[posStride * fNumVerts];
        S->read(posStride * fNumVerts, fPosDelta);
    } else {
        fPosDelta = NULL;
    }
    unsigned int colStride = CalcColStride(fEncoding);
    if (colStride != 0) {
        fCol = new unsigned char[colStride * fNumVerts];
        S->read(colStride * fNumVerts, fCol);
    } else {
        fCol = NULL;
    }
}

void plSpanInstance::write(hsStream* S) {
    S->write(sizeof(fL2W), fL2W);
    if (fPosDelta != NULL)
        S->write(CalcPosStride(fEncoding) * fNumVerts, fPosDelta);
    if (fCol != NULL)
        S->write(CalcColStride(fEncoding) * fNumVerts, fCol);
}

void plSpanInstance::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plSpanInstance");

    prc->writeTagNoBreak("Local2World");
    prc->getStream()->writeStr(
        plString::Format("[ %.04f, %.04f, %.04f, %.04f "
                         "; %.04f, %.04f, %.04f, %.04f "
                         "; %.04f, %.04f, %.04f, %.04f ]",
                         fL2W[0][0], fL2W[0][1], fL2W[0][2], fL2W[0][3],
                         fL2W[1][0], fL2W[1][1], fL2W[1][2], fL2W[1][3],
                         fL2W[2][0], fL2W[2][1], fL2W[2][2], fL2W[2][3]));
    prc->closeTagNoBreak();

    prc->writeSimpleTag("PosDeltas");
    hsTArray<hsVector3> verts = getPosDeltas();
    for (size_t i=0; i<verts.getSize(); i++)
        verts[i].prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Colors");
    hsTArray<unsigned int> colors = getColors();
    for (size_t i=0; i<colors.getSize(); i++) {
        prc->startTag("Color");
        prc->writeParamHex("value", colors[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->closeTag();
}

void plSpanInstance::prcParse(const pfPrcTag* tag, const plSpanEncoding& encoding,
                              unsigned int numVerts) {
    if (tag->getName() != "plSpanInstance")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fEncoding = encoding;
    fNumVerts = numVerts;

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "Local2World") {
            hsTList<plString> contents = child->getContents();
            if (contents.pop() != "[")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[0][0] = contents.pop().toFloat();
            if (contents.pop() != ",")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[0][1] = contents.pop().toFloat();
            if (contents.pop() != ",")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[0][2] = contents.pop().toFloat();
            if (contents.pop() != ",")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[0][3] = contents.pop().toFloat();
            if (contents.pop() != ";")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[1][0] = contents.pop().toFloat();
            if (contents.pop() != ",")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[1][1] = contents.pop().toFloat();
            if (contents.pop() != ",")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[1][2] = contents.pop().toFloat();
            if (contents.pop() != ",")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[1][3] = contents.pop().toFloat();
            if (contents.pop() != ";")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[2][0] = contents.pop().toFloat();
            if (contents.pop() != ",")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[2][1] = contents.pop().toFloat();
            if (contents.pop() != ",")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[2][2] = contents.pop().toFloat();
            if (contents.pop() != ",")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
            fL2W[2][3] = contents.pop().toFloat();
            if (contents.pop() != "]")
                throw pfPrcParseException(__FILE__, __LINE__, "L2WMatrix Format error");
        } else if (child->getName() == "PosDeltas") {
            if (child->countChildren() != fNumVerts)
                throw pfPrcParseException(__FILE__, __LINE__, "Incorrect vertex count");
            const pfPrcTag* posChild = child->getFirstChild();
            hsTArray<hsVector3> verts;
            verts.setSize(fNumVerts);
            for (size_t i=0; i<fNumVerts; i++) {
                verts[i].prcParse(posChild);
                posChild = posChild->getNextSibling();
            }
            setPosDeltas(verts);
        } else if (child->getName() == "Colors") {
            if (child->countChildren() != fNumVerts)
                throw pfPrcParseException(__FILE__, __LINE__, "Incorrect vertex count");
            const pfPrcTag* colorChild = child->getFirstChild();
            hsTArray<unsigned int> colors;
            colors.setSize(fNumVerts);
            for (size_t i=0; i<fNumVerts; i++) {
                if (colorChild->getName() != "Color")
                    throw pfPrcTagException(__FILE__, __LINE__, colorChild->getName());
                colors[i] = colorChild->getParam("value", "0").toUint();
                colorChild = colorChild->getNextSibling();
            }
            setColors(colors);
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
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

hsTArray<hsVector3> plSpanInstance::getPosDeltas() const {
    hsTArray<hsVector3> verts;
    verts.setSize(fNumVerts);

    switch (fEncoding.getCode() & plSpanEncoding::kPosMask) {
    case plSpanEncoding::kPos888:
        {
            unsigned char* pp = fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                verts[i].X = pp[0] * fEncoding.getPosScale();
                verts[i].Y = pp[1] * fEncoding.getPosScale();
                verts[i].Z = pp[2] * fEncoding.getPosScale();
                pp += 3;
            }
        }
        break;
    case plSpanEncoding::kPos161616:
        {
            unsigned short* pp = (unsigned short*)fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                verts[i].X = pp[0] * fEncoding.getPosScale();
                verts[i].Y = pp[1] * fEncoding.getPosScale();
                verts[i].Z = pp[2] * fEncoding.getPosScale();
                pp += 3;
            }
        }
        break;
    case plSpanEncoding::kPos101010:
        {
            unsigned int* pp = (unsigned int*)fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                verts[i].Z = ((*pp >> 20) & 0x3F) * fEncoding.getPosScale();
                verts[i].Y = ((*pp >> 10) & 0x3F) * fEncoding.getPosScale();
                verts[i].X = ((*pp >>  0) & 0x3F) * fEncoding.getPosScale();
                pp++;
            }
        }
        break;
    case plSpanEncoding::kPos008:
        {
            unsigned char* pp = fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                verts[i].X = 0.0f;
                verts[i].Y = 0.0f;
                verts[i].Z = (*pp) * fEncoding.getPosScale();
                pp++;
            }
        }
        break;
    default:
        for (unsigned int i=0; i<fNumVerts; i++)
            verts[i] = hsVector3(0.0f, 0.0f, 0.0f);
        break;
    }
    return verts;
}

hsTArray<unsigned int> plSpanInstance::getColors() const {
    hsTArray<unsigned int> colors;
    colors.setSize(fNumVerts);

    switch (fEncoding.getCode() & plSpanEncoding::kColMask) {
    case plSpanEncoding::kColA8:
        {
            unsigned char* cp = fCol;
            for (unsigned int i=0; i<fNumVerts; i++) {
                colors[i] = *cp << 24;
                cp++;
            }
        }
        break;
    case plSpanEncoding::kColI8:
        {
            unsigned char* cp = fCol;
            for (unsigned int i=0; i<fNumVerts; i++) {
                colors[i] = (*cp << 16) | (*cp << 8) | (*cp);
                cp++;
            }
        }
        break;
    case plSpanEncoding::kColAI88:
        {
            unsigned short* cp = (unsigned short*)fCol;
            for (unsigned int i=0; i<fNumVerts; i++) {
                colors[i] = ((*cp & 0xFF00) << 16)
                          | ((*cp & 0x00FF) << 16) | ((*cp & 0x00FF) << 8) | (*cp & 0x00FF);
                cp++;
            }
        }
        break;
    case plSpanEncoding::kColRGB888:
        {
            unsigned char* cp = fCol;
            for (unsigned int i=0; i<fNumVerts; i++) {
                colors[i] = (cp[0] << 16) | (cp[1] << 8) | (cp[2]);
                cp += 3;
            }
        }
        break;
    case plSpanEncoding::kColARGB8888:
        {
            unsigned int* cp = (unsigned int*)fCol;
            for (unsigned int i=0; i<fNumVerts; i++) {
                colors[i] = *cp;
                cp++;
            }
        }
        break;
    default:
        for (unsigned int i=0; i<fNumVerts; i++)
            colors[i] = 0;
        break;
    }
    return colors;
}

hsMatrix44 plSpanInstance::getLocalToWorld() const {
    hsMatrix44 l2w;
    l2w(0, 0) = fL2W[0][0];
    l2w(0, 1) = fL2W[0][1];
    l2w(0, 2) = fL2W[0][2];
    l2w(0, 3) = fL2W[0][3];
    l2w(1, 0) = fL2W[1][0];
    l2w(1, 1) = fL2W[1][1];
    l2w(1, 2) = fL2W[1][2];
    l2w(1, 3) = fL2W[1][3];
    l2w(2, 0) = fL2W[2][0];
    l2w(2, 1) = fL2W[2][1];
    l2w(2, 2) = fL2W[2][2];
    l2w(2, 3) = fL2W[2][3];
    return l2w;
}

void plSpanInstance::setPosDeltas(const hsTArray<hsVector3>& verts) {
    if (fPosDelta != NULL)
        delete[] fPosDelta;
    fNumVerts = verts.getSize();
    fPosDelta = new unsigned char[fNumVerts * CalcPosStride(fEncoding)];

    switch (fEncoding.getCode() & plSpanEncoding::kPosMask) {
    case plSpanEncoding::kPos888:
        {
            unsigned char* pp = fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                pp[0] = (unsigned char)(verts[i].X / fEncoding.getPosScale());
                pp[1] = (unsigned char)(verts[i].Y / fEncoding.getPosScale());
                pp[2] = (unsigned char)(verts[i].Z / fEncoding.getPosScale());
                pp += 3;
            }
        }
        break;
    case plSpanEncoding::kPos161616:
        {
            unsigned short* pp = (unsigned short*)fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                pp[0] = (unsigned short)(verts[i].X / fEncoding.getPosScale());
                pp[1] = (unsigned short)(verts[i].X / fEncoding.getPosScale());
                pp[2] = (unsigned short)(verts[i].X / fEncoding.getPosScale());
                pp += 3;
            }
        }
        break;
    case plSpanEncoding::kPos101010:
        {
            unsigned int* pp = (unsigned int*)fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                *pp = ((unsigned int)(verts[i].Z / fEncoding.getPosScale()) & 0x3F) << 20
                    | ((unsigned int)(verts[i].Y / fEncoding.getPosScale()) & 0x3F) << 10
                    | ((unsigned int)(verts[i].X / fEncoding.getPosScale()) & 0x3F);
                pp++;
            }
        }
        break;
    case plSpanEncoding::kPos008:
        {
            unsigned char* pp = fPosDelta;
            for (unsigned int i=0; i<fNumVerts; i++) {
                *pp = (unsigned char)(verts[i].Z / fEncoding.getPosScale());
                pp++;
            }
        }
        break;
    }
}

void plSpanInstance::setColors(const hsTArray<unsigned int>& colors) {
    if (fCol != NULL)
        delete[] fCol;
    // Because of bugs in Cyan's code:
    fCol = NULL;
    return;

    // But it would be:
    fCol = new unsigned char[fNumVerts * CalcColStride(fEncoding)];

    switch (fEncoding.getCode() & plSpanEncoding::kColMask) {
    case plSpanEncoding::kColA8:
        {
            unsigned char* cp = fCol;
            for (unsigned int i=0; i<fNumVerts; i++) {
                *cp = (colors[i] & 0xFF000000) >> 24;
                cp++;
            }
        }
        break;
    case plSpanEncoding::kColI8:
        {
            unsigned char* cp = fCol;
            for (unsigned int i=0; i<fNumVerts; i++) {
                *cp = colors[i] & 0xFF;
                cp++;
            }
        }
        break;
    case plSpanEncoding::kColAI88:
        {
            unsigned short* cp = (unsigned short*)fCol;
            for (unsigned int i=0; i<fNumVerts; i++) {
                *cp = (colors[i] & 0xFFFF0000) >> 16;
                cp++;
            }
        }
        break;
    case plSpanEncoding::kColRGB888:
        {
            unsigned char* cp = fCol;
            for (unsigned int i=0; i<fNumVerts; i++) {
                cp[0] = (colors[i] & 0x00FF0000) >> 16;
                cp[1] = (colors[i] & 0x0000FF00) >> 8;
                cp[2] = (colors[i] & 0x000000FF);
                cp += 3;
            }
        }
        break;
    case plSpanEncoding::kColARGB8888:
        {
            unsigned int* cp = (unsigned int*)fCol;
            for (unsigned int i=0; i<fNumVerts; i++) {
                *cp = colors[i];
                cp++;
            }
        }
        break;
    }
}

void plSpanInstance::setLocalToWorld(const hsMatrix44& l2w) {
    fL2W[0][0] = l2w(0, 0);
    fL2W[0][1] = l2w(0, 1);
    fL2W[0][2] = l2w(0, 2);
    fL2W[0][3] = l2w(0, 3);
    fL2W[1][0] = l2w(1, 0);
    fL2W[1][1] = l2w(1, 1);
    fL2W[1][2] = l2w(1, 2);
    fL2W[1][3] = l2w(1, 3);
    fL2W[2][0] = l2w(2, 0);
    fL2W[2][1] = l2w(2, 1);
    fL2W[2][2] = l2w(2, 2);
    fL2W[2][3] = l2w(2, 3);
}
