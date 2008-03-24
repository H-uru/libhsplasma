#ifndef _PLFONT_H
#define _PLFONT_H

#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"

DllClass plFont : public hsKeyedObject {
public:
    DllClass plCharacter {
    protected:
        unsigned int fBitmapOffset;
        unsigned int fHeight;
        int fBaseline;
        float fLeftKern, fRightKern;

    public:
        plCharacter();
        
        void read(hsStream* S);
        void write(hsStream* S);
        void prcWrite(pfPrcHelper* prc);

        unsigned int getOffset() const;
        unsigned int getHeight() const;
        int getBaseline() const;
        float getLeftKern() const;
        float getRightKern() const;

        void setOffset(unsigned int off);
        void setHeight(unsigned int height);
        void setBaseline(int baseline);
        void setKern(float left, float right);
    };

    static const plCharacter kNullChar;

    enum Flags {
        kFontBold = 0x1,
        kFontItalic = 0x2
    };

protected:
    plString fFace;
    unsigned char fSize, fBPP;
    unsigned int fFlags, fWidth, fHeight;
    unsigned char* fBmpData;
    unsigned short fFirstChar;
    hsTArray<plCharacter> fCharacters;
    int fMaxCharHeight, fFontAscent, fFontDescent;
    //plRenderInfo fRenderInfo;

public:
    plFont();
    virtual ~plFont();

    DECLARE_CREATABLE(plFont)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
    
    void readP2F(hsStream* S);
    void writeP2F(hsStream* S);

    void readBitmap(hsStream* S);
    void writeBitmap(hsStream* S);

    plCharacter& operator[](size_t idx);
    void addCharacter(const plCharacter& add);
    void delCharacter(size_t idx);

    const plString& getName() const;
    unsigned char getSize() const;
    unsigned char getBPP() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned short getFirstChar() const;
    int getMaxCharHeight() const;

    void setName(const plString& name);
    void setSize(unsigned char size);
    void setBPP(unsigned char bpp);
    void setWidth(unsigned int width);
    void setHeight(unsigned int height);
    void setFirstChar(unsigned short first);
    void setMaxCharHeight(int maxCharHeight);

    bool isBold() const;
    bool isItalic() const;
    void setBold(bool bold);
    void setItalic(bool italic);
};

#endif
