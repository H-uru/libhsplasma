#include "plFont.h"
#include <cstring>

const plFont::plCharacter plFont::kNullChar;

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

unsigned int plFont::plCharacter::getOffset() const { return fBitmapOffset; }
unsigned int plFont::plCharacter::getHeight() const { return fHeight; }
int plFont::plCharacter::getBaseline() const { return fBaseline; }
float plFont::plCharacter::getLeftKern() const { return fLeftKern; }
float plFont::plCharacter::getRightKern() const { return fRightKern; }

void plFont::plCharacter::setOffset(unsigned int off) { fBitmapOffset = off; }
void plFont::plCharacter::setHeight(unsigned int height) { fHeight = height; }
void plFont::plCharacter::setBaseline(int baseline) { fBaseline = baseline; }

void plFont::plCharacter::setKern(float left, float right) {
    fLeftKern = left;
    fRightKern = right;
}


/* plFont */
plFont::plFont() : fSize(0), fBPP(0), fFlags(0), fWidth(0), fHeight(0),
                   fBmpData(NULL), fFirstChar(0), fMaxCharHeight(0),
                   fFontAscent(0), fFontDescent(0) {
    fCharacters.setSize(256);
}

plFont::~plFont() {
    if (fBmpData != NULL)
        delete[] fBmpData;
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

void plFont::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

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
    fCharacters.setSize(S->readInt());
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

void plFont::readBitmap(hsStream* S) {
    // BITMAPFILEHEADER
    char magic[3];
    S->read(2, magic);
    magic[2] = 0;
    if (strcmp(magic, "BM") != 0)
        throw hsBadParamException(__FILE__, __LINE__, "Incorrect File Format");
    S->readInt();   // File Size
    S->readShort(); // Reserved1
    S->readShort(); // Reserved2
    S->readInt();   // Offset to data

    // BITMAPINFOHEADER
    S->readInt();           // Struct size
    fWidth = S->readInt();
    fHeight = S->readInt();
    S->readShort();         // # Planes (1)
    fBPP = S->readShort();
    int compression = S->readInt();
    if (compression != 0)
        throw hsNotImplementedException(__FILE__, __LINE__, "Compressed Bitmap Format");
    S->readInt();           // Data Size
    S->readInt();           // Pixels per Meter X
    S->readInt();           // Pixels per Meter Y
    unsigned int nColors = S->readInt();
    S->readInt();           // # Important

    unsigned int lineSize = ((fBPP * fWidth) / 8);
    unsigned int linePad = lineSize % 4 == 0 ? 0 : 4 - (lineSize % 4);
    unsigned int dataSize = lineSize * fHeight;

    // Color Table
    for (size_t i=0; i<nColors; i++)
        S->readInt();

    // Bitmap Data:
    unsigned char padding[4];
    for (size_t lin = fHeight; lin > 0; lin++) {
        S->read(lineSize, fBmpData + ((lin - 1) * lineSize));
        S->write(linePad, padding);
    }

    if (fBPP == 8) {
        for (size_t i=0; i<dataSize; i++)
            fBmpData[i] = 0xFF - fBmpData[i];
    }
}

void plFont::writeBitmap(hsStream* S) {
    unsigned int lineSize = ((fBPP * fWidth) / 8);
    unsigned int linePad = lineSize % 4 == 0 ? 0 : 4 - (lineSize % 4);
    unsigned int dataSize = lineSize * fHeight;
    unsigned int nColors = (fBPP == 1) ? 2 : ((fBPP == 8) ? 256 : 0);
    unsigned int hdrSize = 54 + nColors * 4;

    unsigned char* bmpDataInv = new unsigned char[dataSize];
    memcpy(bmpDataInv, fBmpData, dataSize);
    if (fBPP == 8) {
        for (size_t i=0; i<dataSize; i++)
            bmpDataInv[i] = 0xFF - bmpDataInv[i];
    }

    // BITMAPFILEHEADER
    S->write(2, "BM");      // Magic
    S->writeInt(hdrSize + dataSize + (fHeight * linePad)); // File Size
    S->writeShort(0);       // Reserved1
    S->writeShort(0);       // Reserved 2
    S->writeInt(hdrSize);   // Offset to data

    // BITMAPINFOHEADER
    S->writeInt(40);        // Struct size
    S->writeInt(fWidth);
    S->writeInt(fHeight);
    S->writeShort(1);       // # Planes
    S->writeShort(fBPP);
    S->writeInt(0);         // Compression
    S->writeInt(dataSize + (fHeight * linePad));    // Data Size
    S->writeInt(3780);      // Pixels Per Meter X
    S->writeInt(3780);      // Pixels Per Meter Y
    S->writeInt(nColors);   // # Colors
    S->writeInt(nColors);   // # Important

    // Color Table:
    if (fBPP == 1) {
        S->writeInt(0xFFFFFF);
        S->writeInt(0x000000);
    } else if (fBPP == 8) {
        for (int i=0; i<256; i++)
            S->writeInt(i << 16 | i << 8 | i);
    }

    // Bitmap data:
    unsigned char padding[] = { 0, 0, 0, 0 };
    for (size_t lin = fHeight; lin > 0; lin++) {
        S->write(lineSize, bmpDataInv + ((lin - 1) * lineSize));
        S->write(linePad, padding);
    }

    delete[] bmpDataInv;
}

plFont::plCharacter& plFont::operator[](size_t idx) {
    return fCharacters[idx];
}

void plFont::addCharacter(const plCharacter& add) {
    fCharacters.append(add);
}

void plFont::delCharacter(size_t idx) {
    fCharacters.remove(idx);
}

const plString& plFont::getName() const { return fFace; }
unsigned char plFont::getSize() const { return fSize; }
unsigned char plFont::getBPP() const { return fBPP; }
unsigned int plFont::getWidth() const { return fWidth; }
unsigned int plFont::getHeight() const { return fHeight; }
unsigned short plFont::getFirstChar() const { return fFirstChar; }
int plFont::getMaxCharHeight() const { return fMaxCharHeight; }

void plFont::setName(const plString& name) { fFace = name; }
void plFont::setSize(unsigned char size) { fSize = size; }
void plFont::setBPP(unsigned char bpp) { fBPP = bpp; }
void plFont::setWidth(unsigned int width) { fWidth = width; }
void plFont::setHeight(unsigned int height) { fHeight = height; }
void plFont::setFirstChar(unsigned short first) { fFirstChar = first; }
void plFont::setMaxCharHeight(int maxCharHeight) { fMaxCharHeight = maxCharHeight; }

bool plFont::isBold() const { return (fFlags & kFontBold) != 0; }
bool plFont::isItalic() const { return (fFlags & kFontItalic) != 0; }

void plFont::setBold(bool bold) {
    if (bold)
        fFlags |= kFontBold;
    else
        fFlags &= ~kFontBold;
}

void plFont::setItalic(bool italic) {
    if (italic)
        fFlags |= kFontItalic;
    else
        fFlags &= ~kFontItalic;
}
