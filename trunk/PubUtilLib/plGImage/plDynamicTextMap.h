#ifndef _PLDYNAMICTEXTMAP_H
#define _PLDYNAMICTEXTMAP_H

#include "plMipmap.h"
#include "plFont.h"
#include "CoreLib/hsColor.h"

DllClass plDynamicTextMap : public plMipmap {
public:
    enum Justify { kLeftJustify, kCenter, kRightJustify };
    enum DrawMethods { kImgNoAlpha, kImgBlend, kImgSprite };

    enum FontFlags {
        kFontBold = 0x1,
        kFontItalic = 0x2,
        kFontShadowed = 0x4,
    };

protected:
    unsigned short fVisWidth, fVisHeight;
    bool fHasAlpha, fShadowed;
    Justify fJustify;
    plString fFontFace;
    unsigned short fFontSize;
    unsigned char fFontFlags;
    bool fFontAntiAliasRGB, fFontBlockRGB;
    bool fHasBeenCreated;
    short fLineSpacing;
    hsColorRGBA fFontColor;
    plFont* fCurrFont;
    unsigned int* fInitBuffer;

public:
    plDynamicTextMap();
    virtual ~plDynamicTextMap();

    DECLARE_CREATABLE(plDynamicTextMap)

    void Create(unsigned int width, unsigned int height, bool hasAlpha,
                unsigned int extraWidth, unsigned int extraHeight);

    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);

    void setFont(plString face, unsigned int size, unsigned char flags,
                 bool antiAliasRGB);
    void setJustify(Justify just);
    void setTextColor(const hsColorRGBA& color, bool blockRGB);
};

#endif
