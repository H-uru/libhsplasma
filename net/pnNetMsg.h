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
#include "Util/plString.h"
#include "Sys/plUuid.h"
#include <cstdlib>

enum ENetMsgFieldType {
    kFieldInteger, kFieldFloat, kFieldString, kFieldData, kFieldPtr,
    kFieldVarPtr, kFieldRawData, kFieldRawPtr, kFieldRawVarPtr, kFieldVarCount
};

DllStruct pnNetMsgField {
    ENetMsgFieldType fType;
    unsigned int fCount, fSize;
};

DllStruct pnNetMsg {
    unsigned int fMsgId;
    const char* const fMsgName;
    size_t fFieldCount;
    const pnNetMsgField* fFields;
};

typedef union {
    hsUint32 fUint;
    pl_wchar_t* fString;
    hsUbyte* fData;
} msgparm_t;

#define MAKE_NETMSG(name) \
    static pnNetMsg name = { \
        k##name, #name, \
        (sizeof(name##_Fields) / sizeof(pnNetMsgField)), \
        name##_Fields \
    };

DllExport msgparm_t* NCAllocMessage(const pnNetMsg* msg);
DllExport void NCFreeMessage(msgparm_t* data, const pnNetMsg* msg);
DllExport size_t NCMessageSize(const msgparm_t* data, const pnNetMsg* msg);


/* Other stuff that doesn't really belong anywhere else */
DllStruct pnNetAgeInfo {
    enum { Stride = 0x9A0 };

    plUuid fAgeInstanceId;
    plString fAgeFilename, fAgeInstanceName, fAgeUserName, fDescription;
    hsUint32 fSequenceNumber, fLanguage, fPopulation, fCurrPopulation;

    void read(const unsigned char* buffer);
    void write(unsigned char* buffer);
};

DllExport plUuid NCGetUuid(const msgparm_t& field);

#endif
