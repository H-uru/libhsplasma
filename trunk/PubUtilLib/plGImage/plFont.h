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
    };

    enum Flags {
        kFlagBold = 0x1,
        kFlagItalic = 0x2
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
    plCharacter& operator[](size_t idx);

    DECLARE_CREATABLE(plFont)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
    
    void readP2F(hsStream* S);
    void writeP2F(hsStream* S);
};

#endif
