#include "plDynamicTextMap.h"

plDynamicTextMap::plDynamicTextMap()
                : fVisWidth(0), fVisHeight(0), fHasAlpha(false),
                  fShadowed(false), fJustify(kLeftJustify), fFontSize(0),
                  fFontFlags(0), fFontAntiAliasRGB(false), fFontBlockRGB(false),
                  fHasBeenCreated(false), fLineSpacing(0), fCurrFont(NULL),
                  fInitBuffer(NULL) { }

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
    fUncompressedInfo.fType = UncompressedInfo::kRGB8888;
    //setDeviceRef(NULL);
    //setFont("Arial", 12, 0, true);
    //setTextColor(hsColorRGBA::kBlue, false);
    //setCurrLevel(0);
}

void plDynamicTextMap::readData(hsStream* S) {
    plBitmap::readData(S);
    
    fVisWidth = S->readInt();
    fVisHeight = S->readInt();
    fHasAlpha = S->readBool();

    size_t bufSize = S->readInt();
    fInitBuffer = new unsigned int[bufSize];
    S->readInts(bufSize, (hsUint32*)fInitBuffer);
    Create(fVisWidth, fVisHeight, fHasAlpha, 0, 0);
}

void plDynamicTextMap::writeData(hsStream* S) {
    plBitmap::writeData(S);

    S->writeInt(fVisWidth);
    S->writeInt(fVisHeight);
    S->writeBool(fHasAlpha);

    S->writeInt((fInitBuffer != NULL) ? (fVisHeight * fVisWidth) * sizeof(unsigned int) : 0);
    if (fInitBuffer != NULL)
        S->writeInts(fVisHeight * fVisWidth, (hsUint32*)fInitBuffer);
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
        prc->writeHexStream((fVisHeight * fVisWidth) * sizeof(unsigned int),
                            (unsigned char*)fInitBuffer);
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
            fInitBuffer = new unsigned int[(fVisHeight * fVisWidth)];
            tag->readHexStream((fVisHeight * fVisWidth) * sizeof(unsigned int),
                               (unsigned char*)fInitBuffer);
        }
    } else {
        plBitmap::IPrcParse(tag, mgr);
    }
}
