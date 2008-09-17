#include "plDynamicTextMap.h"
#include "Debug/plDebug.h"

plDynamicTextMap::plDynamicTextMap()
                : fVisWidth(0), fVisHeight(0), fHasAlpha(false),
                  fHasBeenCreated(false), fInitBuffer(NULL) { }

plDynamicTextMap::~plDynamicTextMap() {
    if (fInitBuffer != NULL)
        delete[] fInitBuffer;
}

IMPLEMENT_CREATABLE(plDynamicTextMap, kDynamicTextMap, plMipmap)

void plDynamicTextMap::Create(unsigned int width, unsigned int height,
                              bool hasAlpha, unsigned int extraWidth,
                              unsigned int extraHeight) {
    setConfig(hasAlpha ? kARGB32Config : kRGB32Config);
    fVisWidth = width;
    fVisHeight = height;
    fHasAlpha = hasAlpha;
    fWidth = 1;
    if (width + extraWidth > 1) {
        while (fWidth < (width + extraWidth))
            fWidth *= 2;
    }
    fHeight = 1;
    if (height + extraHeight > 1) {
        while (fHeight < (height + extraHeight))
            fHeight *= 2;
    }

    fHasBeenCreated = true;
    fFlags |= kDontThrowAwayImage;
    fStride = fWidth * 4;
    fNumLevels = 1;
    fCompressionType = kUncompressed;
    fUncompressedInfo.fType = kRGB8888;
}

void plDynamicTextMap::readData(hsStream* S) {
    plBitmap::readData(S);
    
    fVisWidth = S->readInt();
    fVisHeight = S->readInt();
    fHasAlpha = S->readBool();

    fInitBufferLen = S->readInt();
    if (fInitBufferLen != 0) {
        if (fInitBufferLen != (size_t)(fVisWidth * fVisHeight))
            plDebug::Warning("Got incorrect init buffer size");
        fInitBuffer = new unsigned int[fInitBufferLen];
        S->readInts(fInitBufferLen, (hsUint32*)fInitBuffer);
    }
    Create(fVisWidth, fVisHeight, fHasAlpha, 0, 0);
}

void plDynamicTextMap::writeData(hsStream* S) {
    plBitmap::writeData(S);

    S->writeInt(fVisWidth);
    S->writeInt(fVisHeight);
    S->writeBool(fHasAlpha);

    S->writeInt(fInitBufferLen);
    if (fInitBuffer != NULL)
        S->writeInts(fInitBufferLen, (hsUint32*)fInitBuffer);
}

void plDynamicTextMap::IPrcWrite(pfPrcHelper* prc) {
    plBitmap::IPrcWrite(prc);

    prc->startTag("DynTextMapParams");
    prc->writeParam("VisWidth", fVisWidth);
    prc->writeParam("VisHeight", fVisHeight);
    prc->writeParam("HasAlpha", fHasAlpha);
    prc->endTag(true);

    if (fInitBuffer != NULL) {
        prc->writeSimpleTag("InitBuffer");
        prc->writeHexStream(fInitBufferLen, (unsigned char*)fInitBuffer);
        prc->closeTag();
    } else {
        prc->startTag("InitBuffer");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plDynamicTextMap::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DynTextMapParams") {
        fVisWidth = tag->getParam("VisWidth", "0").toUint();
        fVisHeight = tag->getParam("VisHeight", "0").toUint();
        fHasAlpha = tag->getParam("HasAlpha", "false").toBool();
    } else if (tag->getName() == "InitBuffer") {
        if (tag->getParam("NULL", "false").toBool()) {
            fInitBuffer = NULL;
        } else {
            fInitBufferLen = tag->getContents().getSize();
            fInitBuffer = new unsigned int[fInitBufferLen];
            tag->readHexStream(fInitBufferLen, (unsigned char*)fInitBuffer);
        }
    } else {
        plBitmap::IPrcParse(tag, mgr);
    }
}
