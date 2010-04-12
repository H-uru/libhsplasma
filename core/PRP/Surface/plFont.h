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

DllClass plFont : public hsKeyedObject {
    CREATABLE(plFont, kFont, hsKeyedObject)

public:
    DllClass plCharacter {
    protected:
        unsigned int fBitmapOffset, fHeight;
        int fBaseline;
        float fLeftKern, fRightKern;

    public:
        plCharacter();

        void read(hsStream* S);
        void write(hsStream* S);
        void prcWrite(pfPrcHelper* prc);
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
        { fLeftKern = left; fRightKern = right; }
    };

    static const plCharacter kNullChar;

    enum Flags {
        kFontBold = 0x1,
        kFontItalic = 0x2
    };

protected:
    plString fFace;
    unsigned char fSize, fBPP;
    unsigned short fFirstChar;
    unsigned int fFlags, fWidth, fHeight;
    unsigned char* fBmpData;
    hsTArray<plCharacter> fCharacters;
    int fMaxCharHeight;

public:
    plFont();
    virtual ~plFont();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void readP2F(hsStream* S);
    void writeP2F(hsStream* S);

    void readBitmap(hsStream* S);
    void writeBitmap(hsStream* S);

public:
    const plCharacter& operator[](size_t idx) const { return fCharacters[idx]; }
    plCharacter& operator[](size_t idx) { return fCharacters[idx]; }
    void setNumCharacters(size_t count) { fCharacters.setSize(count); }

    const plString& getName() const { return fFace; }
    unsigned char getSize() const { return fSize; }
    unsigned char getBPP() const { return fBPP; }
    unsigned int getWidth() const { return fWidth; }
    unsigned int getHeight() const { return fHeight; }
    unsigned short getFirstChar() const { return fFirstChar; }
    int getMaxCharHeight() const { return fMaxCharHeight; }

    void setName(const plString& name) { fFace = name; }
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
