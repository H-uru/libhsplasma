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

#ifndef _PLFONT_H
#define _PLFONT_H

#include "PRP/KeyedObject/hsKeyedObject.h"

class PLASMA_DLL plFont : public hsKeyedObject
{
    CREATABLE(plFont, kFont, hsKeyedObject)

public:
    class PLASMA_DLL plCharacter
    {
    protected:
        uint32_t fBitmapOffset, fHeight;
        int32_t fBaseline;
        float fLeftKern, fRightKern;

    public:
        plCharacter() HS_NOEXCEPT
            : fBitmapOffset(), fHeight(), fBaseline(),
              fLeftKern(), fRightKern() { }

        void read(hsStream* S);
        void write(hsStream* S) const;
        void prcWrite(pfPrcHelper* prc) const;
        void prcParse(const pfPrcTag* tag);

    public:
        uint32_t getOffset() const { return fBitmapOffset; }
        uint32_t getHeight() const { return fHeight; }
        int32_t getBaseline() const { return fBaseline; }
        float getLeftKern() const { return fLeftKern; }
        float getRightKern() const { return fRightKern; }

        void setOffset(uint32_t off) { fBitmapOffset = off; }
        void setHeight(uint32_t height) { fHeight = height; }
        void setBaseline(int32_t baseline) { fBaseline = baseline; }
        void setLeftKern(float kern) { fLeftKern = kern; }
        void setRightKern(float kern) { fRightKern = kern; }

        void setKern(float left, float right)
        {
            fLeftKern = left;
            fRightKern = right;
        }
    };

    static const plCharacter kNullChar;

    enum Flags
    {
        kFontBold = 0x1,
        kFontItalic = 0x2
    };

protected:
    ST::string fFace;
    uint8_t fSize, fBPP;
    uint16_t fFirstChar;
    uint32_t fFlags, fWidth, fHeight;
    unsigned char* fBmpData;
    std::vector<plCharacter> fCharacters;
    int32_t fMaxCharHeight;

public:
    plFont()
        : fSize(), fBPP(), fFirstChar(), fFlags(), fWidth(), fHeight(),
          fBmpData(), fMaxCharHeight()
    {
        fCharacters.resize(256);
    }

    plFont(const plFont& copy);
    ~plFont();

    plFont& operator=(const plFont& copy);

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    void readP2F(hsStream* S);
    void writeP2F(hsStream* S) const;

    void readBitmap(hsStream* S);
    void writeBitmap(hsStream* S) const;

public:
    const plCharacter& operator[](size_t idx) const { return fCharacters[idx]; }
    plCharacter& operator[](size_t idx) { return fCharacters[idx]; }
    const plCharacter& getCharacter(size_t idx) const { return fCharacters[idx]; }
    plCharacter& getCharacter(size_t idx) { return fCharacters[idx]; }
    const unsigned char* getGlyph(size_t idx) const { return fBmpData + fCharacters[idx].getOffset(); }
    size_t getStride() const { return ((fBPP * fWidth) + 7) / 8; }
    size_t getGlyphSize(size_t idx) const { return fCharacters[idx].getHeight() * getStride(); }
    size_t getNumCharacters() const { return fCharacters.size(); }
    void setNumCharacters(size_t count) { fCharacters.resize(count); }

    const ST::string& getName() const { return fFace; }
    uint8_t getSize() const { return fSize; }
    uint8_t getBPP() const { return fBPP; }
    uint32_t getWidth() const { return fWidth; }
    uint32_t getHeight() const { return fHeight; }
    uint16_t getFirstChar() const { return fFirstChar; }
    int32_t getMaxCharHeight() const { return fMaxCharHeight; }

    void setName(const ST::string& name) { fFace = name; }
    void setSize(uint8_t size) { fSize = size; }
    void setBPP(uint8_t bpp) { fBPP = bpp; }
    void setWidth(uint32_t width) { fWidth = width; }
    void setHeight(uint32_t height) { fHeight = height; }
    void setFirstChar(uint16_t first) { fFirstChar = first; }
    void setMaxCharHeight(int32_t maxCharHeight) { fMaxCharHeight = maxCharHeight; }

    uint32_t getFlags() const { return fFlags; }
    void setFlags(uint32_t flags) { fFlags = flags; }
    bool isBold() const { return (fFlags & kFontBold) != 0; }
    bool isItalic() const { return (fFlags & kFontItalic) != 0; }
    void setBold(bool bold);
    void setItalic(bool italic);
};

#endif
