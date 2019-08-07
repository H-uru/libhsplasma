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

#include "plDynamicTextMap.h"
#include "Debug/plDebug.h"
#include <cstring>

plDynamicTextMap::~plDynamicTextMap()
{
    delete[] fInitBuffer;
}

void plDynamicTextMap::Create(unsigned int width, unsigned int height,
                              bool hasAlpha, unsigned int extraWidth,
                              unsigned int extraHeight)
{
    setConfig(kRGB8888);
    fVisWidth = width;
    fVisHeight = height;
    fHasAlpha = hasAlpha;
    fWidth = 1;
    if (width + extraWidth > 1) {
        while (fWidth < (width + extraWidth))
            fWidth *= 2;
    }
    fHeight = 1;
    if (height + extraHeight > 1) {
        while (fHeight < (height + extraHeight))
            fHeight *= 2;
    }

    fHasBeenCreated = true;
    /*fFlags |= kDontThrowAwayImage;*/
    fStride = fWidth * 4;
    fLevelData.resize(1);
    fCompressionType = kUncompressed;
    fUncompressedInfo.fType = kRGB8888;
}

void plDynamicTextMap::read(hsStream* S, plResManager* mgr)
{
    plBitmap::read(S, mgr);

    fVisWidth = S->readInt();
    fVisHeight = S->readInt();
    fHasAlpha = S->readBool();

    fInitBufferLen = S->readInt();
    if (fInitBufferLen != 0) {
        if (fInitBufferLen != (size_t)(fVisWidth * fVisHeight))
            plDebug::Warning("Got incorrect init buffer size");
        fInitBuffer = new unsigned int[fInitBufferLen];
        S->readInts(fInitBufferLen, (uint32_t*)fInitBuffer);
    }
    Create(fVisWidth, fVisHeight, fHasAlpha, 0, 0);
}

void plDynamicTextMap::write(hsStream* S, plResManager* mgr)
{
    plBitmap::write(S, mgr);

    S->writeInt(fVisWidth);
    S->writeInt(fVisHeight);
    S->writeBool(fHasAlpha);

    S->writeInt(fInitBufferLen);
    if (fInitBuffer)
        S->writeInts(fInitBufferLen, (uint32_t*)fInitBuffer);
}

void plDynamicTextMap::IPrcWrite(pfPrcHelper* prc)
{
    plBitmap::IPrcWrite(prc);

    prc->startTag("DynTextMapParams");
    prc->writeParam("VisWidth", fVisWidth);
    prc->writeParam("VisHeight", fVisHeight);
    prc->writeParam("HasAlpha", fHasAlpha);
    prc->endTag(true);

    if (fInitBuffer) {
        prc->writeSimpleTag("InitBuffer");
        prc->writeHexStream(fInitBufferLen, (unsigned char*)fInitBuffer);
        prc->closeTag();
    } else {
        prc->startTag("InitBuffer");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plDynamicTextMap::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "DynTextMapParams") {
        fVisWidth = tag->getParam("VisWidth", "0").to_uint();
        fVisHeight = tag->getParam("VisHeight", "0").to_uint();
        fHasAlpha = tag->getParam("HasAlpha", "false").to_bool();
    } else if (tag->getName() == "InitBuffer") {
        if (tag->getParam("NULL", "false").to_bool()) {
            fInitBuffer = nullptr;
        } else {
            fInitBufferLen = tag->getContents().size();
            fInitBuffer = new unsigned int[fInitBufferLen];
            tag->readHexStream(fInitBufferLen, (unsigned char*)fInitBuffer);
        }
    } else {
        plBitmap::IPrcParse(tag, mgr);
    }
}

void plDynamicTextMap::setInitBuffer(const unsigned int* buffer, size_t size)
{
    fInitBufferLen = size;
    delete[] fInitBuffer;
    fInitBuffer = new unsigned int[size];
    memcpy(fInitBuffer, buffer, size * sizeof(unsigned int));
}
