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

DllClass plNetMsgStreamHelper : public plCreatable {
    CREATABLE(plNetMsgStreamHelper, kNetMsgStreamHelper, plCreatable)

public:
    enum CompressionType {
        kCompressionNone, kCompressionFailed, kCompressionZlib,
        kCompressionDont
    };

private:
    size_t fUncompressedSize;
    unsigned char fCompressionType;
    size_t fStreamLength;
    unsigned char* fStream;

public:
    plNetMsgStreamHelper();
    ~plNetMsgStreamHelper();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

private:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

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


DllClass plNetMsgStream : public plNetMessage {
    CREATABLE(plNetMsgStream, kNetMsgStream, plNetMessage)

private:
    hsRAMStream fStream;
    unsigned char fCompressionType;

public:
    plNetMsgStream();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

private:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsRAMStream* getStream() { return &fStream; }

    unsigned char getCompressionType() const { return fCompressionType; }
    void setCompressionType(unsigned char type) { fCompressionType = type; }
};

#endif
