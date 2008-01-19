#include "plFont.h"
#include <cstring>

plFont::plFont() : FontSize(-1), FontFlags(0), imgWidth(0),
                   imgHeight(0), maxHeight(0), bpp(0), bmpData(NULL),
                   unknown(0), numLetters(256) {
    memset(FontName, '\0', 256);
    Letters = new FontLetterDef[numLetters];
}

plFont::~plFont() {
    if (bmpData) delete bmpData;
    delete[] Letters;
}

IMPLEMENT_CREATABLE(plFont, kFont, hsKeyedObject)

FontLetterDef& plFont::operator[](int idx) {
    return Letters[idx];
}

void plFont::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    readP2F(S);
}

void plFont::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    writeP2F(S);
}

void plFont::readP2F(hsStream* S) {
    S->read(256, FontName);
    FontSize = S->readByte();
    FontFlags = S->readInt();
    imgWidth = S->readInt();
    imgHeight = S->readInt();
    maxHeight = S->readInt();
    bpp = S->readByte();

    unsigned int dataLen = (bpp * imgWidth * imgHeight) >> 3;
    bmpData = new char[dataLen];
    S->read(dataLen, bmpData);
    unknown = S->readShort();

    numLetters = S->readInt();
    if (Letters) delete[] Letters;
    Letters = new FontLetterDef[numLetters];
    for (int i=0; i<numLetters; i++) {
        Letters[i].Offset = S->readInt();
        Letters[i].lHeight = S->readInt();
        Letters[i].stHeight = S->readInt();
        Letters[i].lPadding = S->readFloat();
        Letters[i].rPadding = S->readFloat();
    }
}

void plFont::writeP2F(hsStream* S) {
    S->write(256, FontName);
    S->writeByte(FontSize);
    S->writeInt(FontFlags);
    S->writeInt(imgWidth);
    S->writeInt(imgHeight);
    S->writeInt(maxHeight);
    S->writeByte(bpp);

    S->write((bpp * imgWidth * imgHeight) >> 3, bmpData);
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

