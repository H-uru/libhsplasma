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

#include "plBitmap.h"

#define BITMAPVER ((unsigned char)2)

const char* plBitmap::kCompressionTypeNames[] = {
    "Uncompressed", "DDS", "JPEG"
};

const char* plBitmap::kSpaceNames[] = {
    "None", "Direct", "Gray", "Index"
};

const char* plBitmap::kUncompressedTypeNames[] = {
    "RGB8888", "RGB4444", "RGB1555", "Inten8", "AInten88"
};

const char* plBitmap::kCompressedTypeNames[] = {
    "Error", "DXT1", "DXT2", "DXT3", "DXT4", "DXT5"
};


plBitmap::plBitmap() : fPixelSize(0), fSpace(0), fFlags(0), fCompressionType(0),
                       fLowModTime(0), fHighModTime(0) { }

void plBitmap::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    IRead(S);
}

void plBitmap::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
    IWrite(S);
}

void plBitmap::IRead(hsStream* S) {
    S->readByte();  // Version == 2
    fPixelSize = S->readByte();
    fSpace = S->readByte();
    fFlags = S->readShort();
    fCompressionType = S->readByte();
    if (fCompressionType == kUncompressed || fCompressionType == kJPEGCompression)
        fUncompressedInfo.fType = S->readByte();
    else {
        fDXInfo.fBlockSize = S->readByte();
        fDXInfo.fCompressionType = S->readByte();
    }
    fLowModTime = S->readInt();
    fHighModTime = S->readInt();
}

void plBitmap::IWrite(hsStream* S) {
    S->writeByte(BITMAPVER);
    S->writeByte(fPixelSize);
    S->writeByte(fSpace);
    S->writeShort(fFlags);
    S->writeByte(fCompressionType);
    if (fCompressionType == kUncompressed || fCompressionType == kJPEGCompression)
        S->writeByte(fUncompressedInfo.fType);
    else {
        S->writeByte(fDXInfo.fBlockSize);
        S->writeByte(fDXInfo.fCompressionType);
    }
    S->writeInt(fLowModTime);
    S->writeInt(fHighModTime);
}

void plBitmap::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("BitmapParams");
    prc->writeParam("PixelSize", fPixelSize);
    prc->writeParam("Space", kSpaceNames[fSpace]);
    prc->writeParamHex("Flags", fFlags);
    prc->endTag(true);

    prc->startTag("Compression");
    prc->writeParam("Type", kCompressionTypeNames[fCompressionType]);
    if (fCompressionType == kUncompressed || fCompressionType == kJPEGCompression)
        prc->writeParam("SubType", kUncompressedTypeNames[fUncompressedInfo.fType]);
    else {
        prc->writeParam("SubType", kCompressedTypeNames[fDXInfo.fCompressionType]);
        prc->writeParam("BlockSize", fDXInfo.fBlockSize);
    }
    prc->endTag(true);

    prc->startTag("ModTime");
    prc->writeParam("low", fLowModTime);
    prc->writeParam("high", fHighModTime);
    prc->endTag(true);
}

void plBitmap::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "BitmapParams") {
        fPixelSize = tag->getParam("PixelSize", "0").toUint();
        fFlags = tag->getParam("Flags", "0").toUint();
        plString space = tag->getParam("Space", "None");
        for (size_t i=0; i<=kIndexSpace; i++) {
            if (space == kSpaceNames[i])
                fSpace = i;
        }
    } else if (tag->getName() == "Compression") {
        plString cType = tag->getParam("Type", "Uncompressed");
        fCompressionType = kUncompressed;
        for (size_t i=0; i<=kJPEGCompression; i++) {
            if (cType == kCompressionTypeNames[i])
                fCompressionType = i;
        }
        if (fCompressionType == kUncompressed || fCompressionType == kJPEGCompression) {
            plString sType = tag->getParam("SubType", "RGB8888");
            fUncompressedInfo.fType = kRGB8888;
            for (size_t i=0; i<=kAInten88; i++) {
                if (sType == kUncompressedTypeNames[i])
                    fUncompressedInfo.fType = i;
            }
        } else {
            plString sType = tag->getParam("SubType", "Error");
            fDXInfo.fCompressionType = kDXTError;
            for (size_t i=0; i<=kDXT5; i++) {
                if (sType == kCompressedTypeNames[i])
                    fDXInfo.fCompressionType = i;
            }
            fDXInfo.fBlockSize = tag->getParam("BlockSize", "0").toUint();
        }
    } else if (tag->getName() == "ModTime") {
        fLowModTime = tag->getParam("low", "0").toUint();
        fHighModTime = tag->getParam("high", "0").toUint();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
