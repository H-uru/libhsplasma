#include "pnNetMsg.h"
#include "Debug/hsExceptions.h"

static msgparm_t AllocBasic(unsigned int size, unsigned int count)
{
    msgparm_t msg;
    if (size == 1)
        msg.fData = new hsUbyte[count];
    else if (size == 2)
        msg.fData = (hsUbyte*)(new hsUint16[count]);
    else if (size == 4)
        msg.fData = (hsUbyte*)(new hsUint32[count]);
    else
        throw hsBadParamException(__FILE__, __LINE__, "Bad variable size");
    return msg;
}

msgparm_t* NCAllocMessage(const pnNetMsg* msg)
{
    if (msg == NULL)
        return NULL;

    msgparm_t* data = new msgparm_t[msg->fFieldCount];
    for (size_t i=0; i<msg->fFieldCount; i++) {
        const pnNetMsgField* field = &msg->fFields[i];
        switch (field->fType) {
        case kFieldInteger:
        case kFieldFloat:
            if (field->fCount == 0)
                // Single Value
                data[i].fUint = 0;
            else
                // Array Value
                data[i] = AllocBasic(field->fSize, field->fCount);
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
        case kFieldString:
        case kFieldVarCount:
            // Variable array -- to be allocated later
            data[i].fData = NULL;
            break;
        case kFieldData:
        case kFieldPtr:
        case kFieldRawData:
        case kFieldRawPtr:
            // Fixed-size array
            data[i].fData = new hsUbyte[field->fSize * field->fCount];
            break;
        }
    }
    return data;
}

void NCFreeMessage(msgparm_t* data, const pnNetMsg* msg)
{
    if (data == NULL)
        return;

    for (size_t i=0; i<msg->fFieldCount; i++) {
        const pnNetMsgField* field = &msg->fFields[i];
        switch (field->fType) {
        case kFieldInteger:
        case kFieldFloat:
            if (field->fCount != 0)
                // Array Value
                delete[] data[i].fData;
            break;
        case kFieldVarCount:
            // Value only, do nothing
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
        case kFieldString:
            // Variable array
            if (data[i].fData != NULL)
                delete[] data[i].fData;
            break;
        case kFieldData:
        case kFieldPtr:
        case kFieldRawData:
        case kFieldRawPtr:
            // Fixed-size array
            delete[] data[i].fData;
            break;
        }
    }
    delete[] data;
}

size_t NCMessageSize(const msgparm_t* data, const pnNetMsg* msg)
{
    size_t bufSize = 0;
    unsigned int size = 0;
    unsigned int count = 0;

    for (size_t i=0; i<msg->fFieldCount; i++) {
        const pnNetMsgField* field = &msg->fFields[i];
        switch (field->fType) {
        case kFieldInteger:
        case kFieldFloat:
            if (field->fCount == 0)
                bufSize += field->fSize;
            else
                bufSize += field->fSize * field->fCount;
            break;
        case kFieldString:
            bufSize += sizeof(hsUint16);
            bufSize += NCstrlen((NCchar_t*)(data[i].fData)) * sizeof(NCchar_t);
            break;
        case kFieldVarCount:
            bufSize += sizeof(hsUint32);
            count = data[i].fUint;
            size = field->fSize;
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
            bufSize += count * size;
            count = 0;
            size = 0;
            break;
        case kFieldData:
        case kFieldPtr:
        case kFieldRawData:
        case kFieldRawPtr:
            bufSize += field->fCount * field->fSize;
            break;
        }
    }
    return bufSize;
}

size_t NCstrlen(const NCchar_t* str)
{
    if (str == NULL)
        return 0;

    const NCchar_t* p = str;
    while (*p++ != 0) /* do nothing */ ;
    return (size_t)((p - str) - 1);
}

plString NCstrToString(const NCchar_t* str)
{
    /* Use UTF-8 to preserve the Unicode data */
    const NCchar_t* ch = str;
    size_t len = 0;
    while (*ch != 0) {
        if (*ch < 0x80)
            len += 1;
        else if (*ch < 0x800)
            len += 2;
        else
            len += 3;
        ch++;
    }

    char* buf = new char[len+1];
    ch = str;
    char* p = buf;
    while (*ch != 0) {
        if (*ch < 0x80) {
            p[0] = *ch;
            p += 1;
        } else if (*ch < 0x800) {
            p[0] = 0xC0 | ((*ch >> 6) & 0x1F);
            p[1] = 0x80 | ((*ch     ) & 0x3F);
            p += 2;
        } else {
            p[0] = 0xE0 | ((*ch >> 12) & 0x0F);
            p[1] = 0x80 | ((*ch >>  6) & 0x3F);
            p[2] = 0x80 | ((*ch      ) & 0x3F);
            p += 3;
        }
        ch++;
    }
    *p = 0;
    plString result(buf);
    delete[] buf;
    return result;
}

NCchar_t* StringToNCstr(const plString& str)
{
    /* Use UTF-8 to preserve the Unicode data */
    size_t len = 0;
    const char* ch = str.cstr();
    while (*ch != 0) {
        if ((*ch & 0xF0) == 0xE0) {
            if ((ch[1] == 0) || (ch[2] == 0))
                throw hsBadParamException(__FILE__, __LINE__, "Invalid UTF-8 Data");
            if ((ch[1] & 0xC0) != 0x80 || (ch[2] & 0xC0) != 0x80)
                throw hsBadParamException(__FILE__, __LINE__, "Invalid UTF-8 Data");
            ch += 3;
        } else if ((*ch & 0xE0) == 0xC0) {
            if (ch[1] == 0)
                throw hsBadParamException(__FILE__, __LINE__, "Invalid UTF-8 Data");
            if ((ch[1] & 0xC0) != 0x80)
                throw hsBadParamException(__FILE__, __LINE__, "Invalid UTF-8 Data");
            ch += 2;
        } else {
            if ((*ch & 0xC0) == 0x80)
                throw hsBadParamException(__FILE__, __LINE__, "Invalid UTF-8 Data");
            ch += 1;
        }
        len++;
    }

    NCchar_t* buf = new NCchar_t[len+1];
    ch = str.cstr();
    NCchar_t* p = buf;
    while (*ch != 0) {
        if ((*ch & 0xF0) == 0xE0) {
            *p = ((ch[0] & 0x0F) << 12)
               | ((ch[1] & 0x3F) <<  6)
               | ((ch[2] & 0x3F)      );
            ch += 3;
        } else if ((*ch & 0xE0) == 0xC0) {
            *p = ((ch[0] & 0x1F) << 6)
               | ((ch[1] & 0x3F)     );
            ch += 2;
        } else {
            *p = *ch & 0x7F;
        }
        p++;
    }
    *p = 0;
    return buf;
}
