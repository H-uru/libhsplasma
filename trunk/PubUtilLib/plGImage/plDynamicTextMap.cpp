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
    setFont("Arial", 12, 0, true);
    setTextColor(hsColorRGBA::kBlue, false);
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

    // Another fine product of the Cyan Worlds, Inc. Usefulness Department:
    delete[] fInitBuffer;
    fInitBuffer = NULL;
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

void plDynamicTextMap::prcWrite(pfPrcHelper* prc) {
    plBitmap::prcWrite(prc);

    prc->startTag("DynTextMapParams");
    prc->writeParam("VisWidth", fVisWidth);
    prc->writeParam("VisHeight", fVisHeight);
    prc->writeParam("HasAlpha", fHasAlpha);
    prc->endTag(true);

    if (fInitBuffer != NULL) {
        prc->writeTagNoBreak("InitBuffer");
        unsigned char* ptr = (unsigned char*)fInitBuffer;
        for (size_t i=0; i<(fVisHeight * fVisWidth)*sizeof(unsigned int); i++)
             prc->getStream()->writeStr(plString::Format("%02X", ptr[i]));
        prc->closeTagNoBreak();
    } else {
        prc->startTag("InitBuffer");
        prc->writeParam("Present", false);
        prc->endTag(true);
    }
}

void plDynamicTextMap::setFont(plString face, unsigned int size,
                               unsigned char flags, bool antiAliasRGB) {
    fFontSize = size;
    fFontFlags = flags;
    fFontAntiAliasRGB = antiAliasRGB;
    /*
    fCurrFont = plFontCache::GetFont(fFontFace, fFontSize, fFontFlags & 3);
    if (fCurrFont == NULL) {
        fFontFace = "Arial";
        fCurrFont = plFontCache::GetFont(fFontFace, fFontSize, fFontFlags & 3);
    }
    fCurrFont->fRenderInfo.fFlags &= ~(kRenderJustYCenter | kRenderJustYBottom);
    fCurrFont->fRenderInfo.fFlags |= kRenderJustYTop;
    */
    setJustify(fJustify);
}

void plDynamicTextMap::setJustify(Justify just) {
    fJustify = just;

    /*
    switch (fJustify) {
    case kLeftJustify:
        fCurrFont->fRenderInfo.fFlags &= ~(kRenderJustXRight | kRenderJustXCenter);
        fCurrFont->fRenderInfo.fFlags |= kRenderJustXForceLeft;
        break;
    case kCenter:
        fCurrFont->fRenderInfo.fFlags &= ~(kRenderJustXRight | kRenderJustXForceLeft);
        fCurrFont->fRenderInfo.fFlags |= kRenderJustXCenter;
        break;
    case kRightJustify:
        fCurrFont->fRenderInfo.fFlags &= ~(kRenderJustXCenter | kRenderJustXForceLeft);
        fCurrFont->fRenderInfo.fFlags |= kRenderJustXRight;
        break;
    }
    */
}

void plDynamicTextMap::setTextColor(const hsColorRGBA& color, bool blockRGB) {
    fFontColor = color;
    fFontBlockRGB = blockRGB;

    /*
    fCurrFont->setRenderColor((fFontColor.a * 256) << 24 |
                              (fFontColor.b * 256) << 16 |
                              (fFontColor.g * 256) << 8  |
                              (fFontColor.r * 256));
    */  
}

