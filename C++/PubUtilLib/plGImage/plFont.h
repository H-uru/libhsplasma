#ifndef _PLFONT_H
#define _PLFONT_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsStream.h"

typedef struct FontLetterDef {
    unsigned int Offset;
    int lHeight;
    int stHeight;
    float lPadding;
    float rPadding;
};

class plFont : public hsKeyedObject {
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
    plFont(PlasmaVer pv = pvUnknown);
    ~plFont();

    FontLetterDef& operator[](int idx);

    void read(hsStream *S);
    void write(hsStream *S);
    void readP2F(hsStream *S);
    void writeP2F(hsStream *S);
};

#endif

