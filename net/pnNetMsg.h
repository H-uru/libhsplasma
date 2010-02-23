#ifndef _PNNETMSG_H
#define _PNNETMSG_H

#include "PlasmaDefs.h"
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

typedef unsigned short NCchar_t;

typedef union {
    hsUint32 fUint;
    NCchar_t* fString;
    hsUbyte* fData;
} msgparm_t;

DllExport msgparm_t* NCAllocMessage(const pnNetMsg* msg);
DllExport void NCFreeMessage(msgparm_t* data, const pnNetMsg* msg);
DllExport size_t NCMessageSize(const msgparm_t* data, const pnNetMsg* msg);

#define MAKE_NETMSG(name) \
    static pnNetMsg name = { \
        k##name, #name, \
        (sizeof(name##_Fields) / sizeof(pnNetMsgField)), \
        name##_Fields \
    };

/* Some NCstring utilities */
DllExport size_t NCstrlen(const NCchar_t* str);
DllExport plString NCstrToString(const NCchar_t* str);
DllExport NCchar_t* StringToNCstr(const plString& str);
DllExport void NCstrlower(NCchar_t* str);

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
