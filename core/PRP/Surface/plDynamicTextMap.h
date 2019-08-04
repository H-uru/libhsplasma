/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLDYNAMICTEXTMAP_H
#define _PLDYNAMICTEXTMAP_H

#include "plMipmap.h"
#include "plFont.h"
#include "Sys/hsColor.h"

class PLASMA_DLL plDynamicTextMap : public plMipmap
{
    CREATABLE(plDynamicTextMap, kDynamicTextMap, plMipmap)

public:
    enum Justify { kLeftJustify, kCenter, kRightJustify };
    enum DrawMethods { kImgNoAlpha, kImgBlend, kImgSprite };

    enum FontFlags
    {
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
    plDynamicTextMap()
        : fVisWidth(), fVisHeight(), fHasAlpha(), fHasBeenCreated(),
          fInitBuffer(), fInitBufferLen() { }
    ~plDynamicTextMap();

    void Create(unsigned int width, unsigned int height, bool hasAlpha,
                unsigned int extraWidth, unsigned int extraHeight);

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

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
