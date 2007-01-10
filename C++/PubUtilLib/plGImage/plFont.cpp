#include "plFont.h"
#include <string.h>

plFont::plFont(PlasmaVer pv) : FontSize(-1), FontFlags(0), imgWidth(0),
                   imgHeight(0), maxHeight(0), bpp(0), bmpData(NULL),
                   unknown(0), numLetters(256) {
    memset(FontName, '\0', 256);
    Letters = new FontLetterDef[numLetters];
}

plFont::plFont(const char* FileName, PlasmaVer pv)
       : hsKeyedObject::hsKeyedObject(pv) {
    hsStream *FS = new hsStream(FileName, fmRead);
    readP2F(FS);
    delete FS;
}

plFont::~plFont() {
    if (bmpData) delete bmpData;
    delete [] Letters;
}

FontLetterDef& plFont::operator[](int idx) {
    return Letters[idx];
}

void plFont::read(hsStream *S) {
    hsKeyedObject::read(S);
    readP2F(S);
}

void plFont::write(hsStream *S) {
    hsKeyedObject::write(S);
    writeP2F(S);
}

void plFont::readP2F(hsStream *S) {
    strncpy(FontName, S->readStr(256), 256);
    FontSize = S->readByte();
    FontFlags = S->readInt();
    imgWidth = S->readInt();
    imgHeight = S->readInt();
    maxHeight = S->readInt();
    bpp = S->readByte();

    bmpData = S->readStr((bpp * imgWidth * imgHeight) >> 3);
    unknown = S->readShort();

    numLetters = S->readInt();
    if (Letters) delete [] Letters;
    Letters = new FontLetterDef[numLetters];
    for (int i=0; i<numLetters; i++) {
        Letters[i].Offset = S->readInt();
        Letters[i].lHeight = S->readInt();
        Letters[i].stHeight = S->readInt();
        Letters[i].lPadding = S->readFloat();
        Letters[i].rPadding = S->readFloat();
    }
}

void plFont::writeP2F(hsStream *S) {
    S->writeStr(FontName, 256);
    S->writeByte(FontSize);
    S->writeInt(FontFlags);
    S->writeInt(imgWidth);
    S->writeInt(imgHeight);
    S->writeInt(maxHeight);
    S->writeByte(bpp);

    S->writeStr(bmpData, (bpp * imgWidth * imgHeight) >> 3);
    S->writeShort(unknown);

    S->writeInt(numLetters);
    for (int i=0; i<numLetters; i++) {
        S->writeInt(Letters[i].Offset);
        S->writeInt(Letters[i].lHeight);
        S->writeInt(Letters[i].stHeight);
        S->writeFloat(Letters[i].lPadding);
        S->writeFloat(Letters[i].rPadding);
    }
}

