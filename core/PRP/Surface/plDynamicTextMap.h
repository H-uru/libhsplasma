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
    unsigned int fVisWidth, fVisHeight;
    bool fHasAlpha, fHasBeenCreated;
    unsigned int* fInitBuffer;
    size_t fInitBufferLen;

public:
    plDynamicTextMap();
    virtual ~plDynamicTextMap();

    DECLARE_CREATABLE(plDynamicTextMap)

    void Create(unsigned int width, unsigned int height, bool hasAlpha,
                unsigned int extraWidth, unsigned int extraHeight);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getVisWidth() const;
    unsigned int getVisHeight() const;
    bool hasAlpha() const;
    const unsigned int* getInitBuffer() const;
    size_t getInitBufferSize() const;

    void setVisWidth(unsigned int width);
    void setVisHeight(unsigned int height);
    void setHasAlpha(bool hasAlpha);
    void setInitBuffer(const unsigned int* buffer, size_t size);
};

#endif
