#include "plFont.h"
#include <cstring>

/* plFont::plCharacter */
plFont::plCharacter::plCharacter()
                   : fBitmapOffset(0), fHeight(0), fBaseline(0),
                     fLeftKern(0.0f), fRightKern(0.0f) { }

void plFont::plCharacter::read(hsStream* S) {
    fBitmapOffset = S->readInt();
    fHeight = S->readInt();
    fBaseline = S->readInt();
    fLeftKern = S->readFloat();
    fRightKern = S->readFloat();
}

void plFont::plCharacter::write(hsStream* S) {
    S->writeInt(fBitmapOffset);
    S->writeInt(fHeight);
    S->writeInt(fBaseline);
    S->writeFloat(fLeftKern);
    S->writeFloat(fRightKern);
}

void plFont::plCharacter::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plCharacter");
    prc->writeParam("BitmapOffset", fBitmapOffset);
    prc->writeParam("Height", fHeight);
    prc->writeParam("Baseline", fBaseline);
    prc->writeParam("LeftKern", fLeftKern);
    prc->writeParam("RightKern", fRightKern);
    prc->endTag(true);
}

/* plFont */
plFont::plFont() : fSize(0), fBPP(0), fFlags(0), fWidth(0), fHeight(0),
                   fBmpData(NULL), fFirstChar(0), fMaxCharHeight(0),
                   fFontAscent(0), fFontDescent(0) { }

plFont::~plFont() {
    if (fBmpData != NULL)
        delete[] fBmpData;
}

plFont::plCharacter& plFont::operator[](size_t idx) {
    return fCharacters[idx];
}

IMPLEMENT_CREATABLE(plFont, kFont, hsKeyedObject)

void plFont::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    readP2F(S);
}

void plFont::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    writeP2F(S);
}

void plFont::prcWrite(pfPrcHelper* prc) {
    hsKeyedObject::prcWrite(prc);

    prc->startTag("FontParams");
    prc->writeParam("Fontface", fFace);
    prc->writeParam("Size", fSize);
    prc->writeParam("Flags", fFlags);
    prc->writeParam("FirstChar", fFirstChar);
    prc->endTag(true);

    prc->startTag("BitmapParams");
    prc->writeParam("Width", fWidth);
    prc->writeParam("Height", fHeight);
    prc->writeParam("BPP", fBPP);
    prc->writeParam("MaxCharHeight", fMaxCharHeight);
    prc->writeParam("src", "");
    prc->endTag(true);

    prc->writeSimpleTag("Characters");
    for (size_t i=0; i<fCharacters.getSize(); i++)
        fCharacters[i].prcWrite(prc);
    prc->closeTag();
}

void plFont::readP2F(hsStream* S) {
    char buf[256];
    S->read(256, buf);
    buf[255] = 0;
    fFace = buf;
    
    fSize = S->readByte();
    fFlags = S->readInt();
    fWidth = S->readInt();
    fHeight = S->readInt();
    fMaxCharHeight = S->readInt();
    fBPP = S->readByte();

    unsigned int size = (fBPP * fWidth * fHeight) / 8;
    if (size > 0) {
        fBmpData = new unsigned char[size];
        S->read(size, fBmpData);
    }

    fFirstChar = S->readShort();
    fCharacters.setSizeNull(S->readInt());
    for (size_t i=0; i<fCharacters.getSize(); i++)
        fCharacters[i].read(S);

    //ICalcFontAscent();
}

void plFont::writeP2F(hsStream* S) {
    char buf[256];
    snprintf(buf, 256, fFace.cstr());
    S->write(256, buf);
    
    S->writeByte(fSize);
    S->writeInt(fFlags);
    S->writeInt(fWidth);
    S->writeInt(fHeight);
    S->writeInt(fMaxCharHeight);
    S->writeByte(fBPP);

    S->write((fBPP * fWidth * fHeight) / 8, fBmpData);
    
    S->writeShort(fFirstChar);
    S->writeInt(fCharacters.getSize());
    for (size_t i=0; i<fCharacters.getSize(); i++)
        fCharacters[i].write(S);
}

