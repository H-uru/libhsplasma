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

#ifndef _PLNETMSGSTREAM_H
#define _PLNETMSGSTREAM_H

#include "plNetMessage.h"
#include "Stream/hsRAMStream.h"
#include "Util/plZlib.h"

class PLASMA_DLL plNetMsgStreamHelper : public plCreatable
{
    CREATABLE(plNetMsgStreamHelper, kNetMsgStreamHelper, plCreatable)

public:
    enum CompressionType
    {
        kCompressionNone, kCompressionFailed, kCompressionZlib,
        kCompressionDont
    };

private:
    size_t fUncompressedSize;
    unsigned char fCompressionType;
    size_t fStreamLength;
    unsigned char* fStream;

public:
    plNetMsgStreamHelper()
        : fUncompressedSize(), fCompressionType(), fStreamLength(), fStream() { }
    ~plNetMsgStreamHelper();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

private:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const unsigned char* getStream() const { return fStream; }
    unsigned int getStreamLength() const { return fStreamLength; }
    unsigned int getUncompressedSize() const { return fUncompressedSize; }
    unsigned char getCompressionType() const { return fCompressionType; }

    void setStream(const unsigned char* stream, unsigned int length);
    void setUncompressedSize(unsigned int size) { fUncompressedSize = size; }
    void setCompressionType(unsigned char type) { fCompressionType = type; }

private:
    void decompress(int offset);
};


class PLASMA_DLL plNetMsgStream : public plNetMessage
{
    CREATABLE(plNetMsgStream, kNetMsgStream, plNetMessage)

private:
    hsRAMStream fStream;
    unsigned char fCompressionType;

public:
    plNetMsgStream() : fCompressionType() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

private:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    hsRAMStream* getStream() { return &fStream; }

    unsigned char getCompressionType() const { return fCompressionType; }
    void setCompressionType(unsigned char type) { fCompressionType = type; }
};

#endif
