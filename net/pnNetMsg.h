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

#ifndef _PNNETMSG_H
#define _PNNETMSG_H

#include "PlasmaDefs.h"
#include "Protocol.h"
#include "Sys/plUuid.h"
#include <string_theory/string>
#include <cstdlib>
#include <cstring>

enum ENetMsgFieldType
{
    kFieldInteger, kFieldFloat, kFieldString, kFieldData, kFieldPtr,
    kFieldVarPtr, kFieldRawData, kFieldRawPtr, kFieldRawVarPtr, kFieldVarCount
};

struct PLASMANET_DLL pnNetMsgField
{
    ENetMsgFieldType fType;
    unsigned int fCount, fSize;
};

struct PLASMANET_DLL pnNetMsg
{
    unsigned int fMsgId;
    const char* const fMsgName;
    size_t fFieldCount;
    const pnNetMsgField* fFields;
};

typedef union
{
    uint32_t fUint;
    char16_t* fString;
    uint8_t* fData;
} msgparm_t;

// More work is needed to clean this up, but it's better than generating
// a bunch of unaligned reads and writes.
template <typename T>
T NCReadBuffer(const uint8_t*& buffer)
{
    T result;
    memcpy(&result, buffer, sizeof(result));
    buffer += sizeof(result);
    return result;
}

template <typename T>
void NCWriteBuffer(uint8_t*& buffer, T value)
{
    memcpy(buffer, &value, sizeof(value));
    buffer += sizeof(value);
}

template <size_t fixedSize>
ST::string NCReadUtf16(const uint8_t*& buffer)
{
    char16_t u16buf[fixedSize];
    memcpy(u16buf, buffer, sizeof(u16buf));
    buffer += sizeof(u16buf);
    u16buf[fixedSize-1] = 0;
    return ST::string::from_utf16(u16buf);
}

template <size_t fixedSize>
void NCWriteUtf16(uint8_t*& buffer, const ST::string& str)
{
    memset(buffer, 0, fixedSize * sizeof(char16_t));
    const ST::utf16_buffer u16buf = str.to_utf16();
    const size_t chars = (u16buf.size() > fixedSize - 1) ? fixedSize - 1 : u16buf.size();
    memcpy(buffer, u16buf.data(), chars * sizeof(char16_t));
    buffer += fixedSize * sizeof(char16_t);
}

#define MAKE_NETMSG(name) \
    static pnNetMsg name = { \
        k##name, #name, \
        (sizeof(name##_Fields) / sizeof(pnNetMsgField)), \
        name##_Fields \
    };

PLASMANET_DLL msgparm_t* NCAllocMessage(const pnNetMsg* msg);
PLASMANET_DLL char16_t* NCCopyString(const ST::string& string);
PLASMANET_DLL void NCFreeMessage(msgparm_t* data, const pnNetMsg* msg);
PLASMANET_DLL size_t NCMessageSize(const msgparm_t* data, const pnNetMsg* msg);


/* Other stuff that doesn't really belong anywhere else */
struct PLASMANET_DLL pnNetAgeInfo
{
    enum { Stride = 0x9A0 };

    plUuid fAgeInstanceId;
    ST::string fAgeFilename, fAgeInstanceName, fAgeUserName, fDescription;
    uint32_t fSequenceNumber, fLanguage, fPopulation, fCurrPopulation;

    void read(const unsigned char* buffer);
    void write(unsigned char* buffer);
};

PLASMANET_DLL plUuid NCGetUuid(const msgparm_t& field);

#endif
