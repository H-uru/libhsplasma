#ifndef _PLDYNAMICTEXTMAP_H
#define _PLDYNAMICTEXTMAP_H

#include "plMipmap.h"
#include "plFont.h"
#include "Sys/hsColor.h"

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
    bool fHasAlpha, fHasBeenCreated;
    unsigned int* fInitBuffer;
    size_t fInitBufferLen;

public:
    plDynamicTextMap();
    virtual ~plDynamicTextMap();

    DECLARE_CREATABLE(plDynamicTextMap)

    void Create(unsigned int width, unsigned int height, bool hasAlpha,
                unsigned int extraWidth, unsigned int extraHeight);

protected:
    virtual void readData(hsStream* S);
    virtual void writeData(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
