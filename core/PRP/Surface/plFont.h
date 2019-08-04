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
        unsigned int fBitmapOffset, fHeight;
        int fBaseline;
        float fLeftKern, fRightKern;

    public:
        plCharacter() noexcept
            : fBitmapOffset(), fHeight(), fBaseline(),
              fLeftKern(), fRightKern() { }

        void read(hsStream* S);
        void write(hsStream* S) const;
        void prcWrite(pfPrcHelper* prc) const;
        void prcParse(const pfPrcTag* tag);

    public:
        unsigned int getOffset() const { return fBitmapOffset; }
        unsigned int getHeight() const { return fHeight; }
        int getBaseline() const { return fBaseline; }
        float getLeftKern() const { return fLeftKern; }
        float getRightKern() const { return fRightKern; }

        void setOffset(unsigned int off) { fBitmapOffset = off; }
        void setHeight(unsigned int height) { fHeight = height; }
        void setBaseline(int baseline) { fBaseline = baseline; }

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
    unsigned char fSize, fBPP;
    unsigned short fFirstChar;
    unsigned int fFlags, fWidth, fHeight;
    unsigned char* fBmpData;
    std::vector<plCharacter> fCharacters;
    int fMaxCharHeight;

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
    size_t getNumCharacters() const { return fCharacters.size(); }
    void setNumCharacters(size_t count) { fCharacters.resize(count); }

    const ST::string& getName() const { return fFace; }
    unsigned char getSize() const { return fSize; }
    unsigned char getBPP() const { return fBPP; }
    unsigned int getWidth() const { return fWidth; }
    unsigned int getHeight() const { return fHeight; }
    unsigned short getFirstChar() const { return fFirstChar; }
    int getMaxCharHeight() const { return fMaxCharHeight; }

    void setName(const ST::string& name) { fFace = name; }
    void setSize(unsigned char size) { fSize = size; }
    void setBPP(unsigned char bpp) { fBPP = bpp; }
    void setWidth(unsigned int width) { fWidth = width; }
    void setHeight(unsigned int height) { fHeight = height; }
    void setFirstChar(unsigned short first) { fFirstChar = first; }
    void setMaxCharHeight(int maxCharHeight) { fMaxCharHeight = maxCharHeight; }

    bool isBold() const { return (fFlags & kFontBold) != 0; }
    bool isItalic() const { return (fFlags & kFontItalic) != 0; }
    void setBold(bool bold);
    void setItalic(bool italic);
};

#endif
