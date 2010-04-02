#ifndef _PLDYNAMICTEXTMAP_H
#define _PLDYNAMICTEXTMAP_H

#include "plMipmap.h"
#include "plFont.h"
#include "Sys/hsColor.h"

DllClass plDynamicTextMap : public plMipmap {
    CREATABLE(plDynamicTextMap, kDynamicTextMap, plMipmap)

public:
    enum Justify { kLeftJustify, kCenter, kRightJustify };
    enum DrawMethods { kImgNoAlpha, kImgBlend, kImgSprite };

    enum FontFlags {
        kFontBold = 0x1,
        kFontItalic = 0x2,
        kFontShadowed = 0x4,
    };

protected:
    unsigned int fVisWidth, fVisHeight;
    bool fHasAlpha, fHasBeenCreated;
    unsigned int* fInitBuffer;
    size_t fInitBufferLen;

public:
    plDynamicTextMap();
    virtual ~plDynamicTextMap();

    void Create(unsigned int width, unsigned int height, bool hasAlpha,
                unsigned int extraWidth, unsigned int extraHeight);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getVisWidth() const { return fVisWidth; }
    unsigned int getVisHeight() const { return fVisHeight; }
    bool hasAlpha() const { return fHasAlpha; }
    size_t getInitBufferSize() const { return fInitBufferLen; }
    const unsigned int* getInitBuffer() const { return fInitBuffer; }

    void setVisWidth(unsigned int width) { fVisWidth = width; }
    void setVisHeight(unsigned int height) { fVisHeight = height; }
    void setHasAlpha(bool hasAlpha) { fHasAlpha = hasAlpha; }
    void setInitBuffer(const unsigned int* buffer, size_t size);
};

#endif
