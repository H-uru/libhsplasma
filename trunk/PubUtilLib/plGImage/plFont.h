#ifndef _PLFONT_H
#define _PLFONT_H

#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "CoreLib/hsStream.h"

DllStruct FontLetterDef {
    unsigned int Offset;
    int lHeight;
    int stHeight;
    float lPadding;
    float rPadding;
};

DllClass plFont : public hsKeyedObject {
protected:
    char FontName[256];
    char FontSize;
    int FontFlags;
    int imgWidth;
    int imgHeight;
    int maxHeight;
    char bpp;

    char* bmpData;
    short unknown;

    int numLetters;
    FontLetterDef * Letters;

public:
    plFont();
    virtual ~plFont();

    DECLARE_CREATABLE(plFont)

    FontLetterDef& operator[](int idx);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    void readP2F(hsStream* S);
    void writeP2F(hsStream* S);
};

#endif

