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

#include "plNetMsgStream.h"
#include <cstring>

/* plNetMsgStreamHelper */
plNetMsgStreamHelper::~plNetMsgStreamHelper()
{
    delete[] fStream;
}

void plNetMsgStreamHelper::read(hsStream* S, plResManager* mgr)
{
    fUncompressedSize = S->readInt();
    fCompressionType = S->readByte();
    fStreamLength = S->readInt();
    delete[] fStream;
    if (fStreamLength > 0) {
        fStream = new unsigned char[fStreamLength];
        S->read(fStreamLength, fStream);
        decompress(2);
    } else {
        fStream = nullptr;
    }
}

void plNetMsgStreamHelper::write(hsStream* S, plResManager* mgr)
{
    unsigned char* outStream = fStream;
    fUncompressedSize = fStreamLength;
    if (fCompressionType == kCompressionZlib) {
        unsigned char* tempStream = nullptr;
        if (plZlib::Compress(tempStream, fStreamLength,
                             fStream + 2, fUncompressedSize - 2)) {
            outStream = new unsigned char[fStreamLength + 2];
            memcpy(outStream, fStream, 2);
            memcpy(outStream + 2, tempStream, fStreamLength);
            fStreamLength += 2;
        } else {
            fStreamLength = fUncompressedSize;
            fCompressionType = kCompressionNone;
            delete[] tempStream;
        }
    }

    S->writeInt(fUncompressedSize);
    S->writeByte(fCompressionType);
    S->writeInt(fStreamLength);
    S->write(fStreamLength, outStream);

    if (fCompressionType == kCompressionZlib)
        delete[] outStream;
}

void plNetMsgStreamHelper::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("Stream");
    prc->writeParam("UncompressedSize", (unsigned long)fUncompressedSize);
    prc->writeParam("CompressionType", fCompressionType);
    prc->endTag();
    prc->writeHexStream(fStreamLength, fStream);
    prc->closeTag();
}

void plNetMsgStreamHelper::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Stream") {
        fUncompressedSize = tag->getParam("UncompressedSize", "0").to_uint();
        fCompressionType = tag->getParam("CompressionType", "0").to_uint();

        delete[] fStream;
        fStreamLength = tag->getContents().size();
        fStream = new unsigned char[fStreamLength];
        tag->readHexStream(fStreamLength, fStream);
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plNetMsgStreamHelper::setStream(const unsigned char* stream, unsigned int length)
{
    delete[] fStream;
    fStreamLength = length;
    if (fStreamLength != 0) {
        fStream = new unsigned char[fStreamLength];
        memcpy(fStream, stream, fStreamLength);
    } else {
        fStream = nullptr;
    }
}

void plNetMsgStreamHelper::decompress(int offset)
{
    if (fCompressionType == kCompressionZlib) {
        unsigned char* newStream = new unsigned char[fUncompressedSize];
        fUncompressedSize -= offset;
        if (plZlib::Uncompress(newStream + offset, fUncompressedSize,
                               fStream + offset, fStreamLength - offset)) {
            memcpy(newStream, fStream, offset);
            delete[] fStream;
            fStream = newStream;
            fStreamLength = fUncompressedSize + offset;
        } else {
            delete[] newStream;
            fCompressionType = kCompressionFailed;
        }
        fUncompressedSize += offset;
    }
}


/* plNetMsgStream */
void plNetMsgStream::read(hsStream* S, plResManager* mgr)
{
    plNetMessage::read(S, mgr);

    plNetMsgStreamHelper helper;
    helper.read(S, mgr);
    fStream.setVer(S->getVer());
    fStream.copyFrom(helper.getStream(), helper.getStreamLength());
    fCompressionType = helper.getCompressionType();
    // TODO: Decompression
}

void plNetMsgStream::write(hsStream* S, plResManager* mgr)
{
    plNetMessage::write(S, mgr);

    plNetMsgStreamHelper helper;
    unsigned char* buf = new unsigned char[fStream.size()];
    fStream.copyTo(buf, fStream.size());
    helper.setStream(buf, fStream.size());
    helper.setCompressionType(fCompressionType);
    // TODO: Compression
    helper.write(S, mgr);
    delete[] buf;
}

void plNetMsgStream::IPrcWrite(pfPrcHelper* prc)
{
    plNetMessage::IPrcWrite(prc);

    plNetMsgStreamHelper helper;
    unsigned char* buf = new unsigned char[fStream.size()];
    fStream.copyTo(buf, fStream.size());
    helper.setStream(buf, fStream.size());
    helper.prcWrite(prc);
    delete[] buf;
}

void plNetMsgStream::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "plNetMsgStreamHelper") {
        plNetMsgStreamHelper helper;
        helper.prcParse(tag, mgr);
        fStream.copyFrom(helper.getStream(), helper.getStreamLength());
        fCompressionType = helper.getCompressionType();
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}
