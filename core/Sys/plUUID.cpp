#include "plUUID.h"

plUUID::plUUID() {
    clear();
}

plUUID::plUUID(const plUUID& init) {
    memcpy(fData, init.fData, sizeof(fData));
}

/*
plUUID::plUUID(const Uuid& init) {
    memcpy(fData, &init, sizeof(fData));
}
*/

plUUID::plUUID(const char* str) {
    fromString(str);
}

void plUUID::read(hsStream* S) {
    S->read(16, fData);
}

void plUUID::write(hsStream* S) {
    S->write(16, fData);
}

void plUUID::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plUUID");
    prc->writeParam("value", toString());
    prc->endTag(true);
}

void plUUID::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plUUID")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fromString(tag->getParam("value", "00000000-0000-0000-0000-000000000000"));
}

void plUUID::clear() {
    memset(fData, 0, sizeof(fData));
}

bool plUUID::isNull() const {
    static unsigned char nullData[16];
    static bool cmpInit = false;
    if (!cmpInit) {
        memset(nullData, 0, sizeof(nullData));
        cmpInit = true;
    }
    return memcmp(nullData, fData, sizeof(fData)) == 0;
}

plString plUUID::toString() const {
    WinUUID udat;
    memcpy(&udat, fData, sizeof(WinUUID));
    return plString::Format("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
             udat.Data1, udat.Data2, udat.Data3,
             udat.Data4[0], udat.Data4[1], udat.Data4[2], udat.Data4[3],
             udat.Data4[4], udat.Data4[5], udat.Data4[6], udat.Data4[7]);
}

void plUUID::fromString(const plString& str) {
    if (str.len() != 36 || str[8] != '-' || str[13] != '-' ||
                           str[18] != '-' || str[23] != '-')
        throw hsBadParamException(__FILE__, __LINE__, "Incorrect UUID format");
    
    WinUUID udat;
    udat.Data1 = str.mid(0, 8).toUint(16);
    udat.Data2 = str.mid(9, 4).toUint(16);
    udat.Data3 = str.mid(14, 4).toUint(16);
    udat.Data4[0] = str.mid(19, 2).toUint(16);
    udat.Data4[1] = str.mid(21, 2).toUint(16);
    udat.Data4[2] = str.mid(24, 2).toUint(16);
    udat.Data4[3] = str.mid(26, 2).toUint(16);
    udat.Data4[4] = str.mid(28, 2).toUint(16);
    udat.Data4[5] = str.mid(30, 2).toUint(16);
    udat.Data4[6] = str.mid(32, 2).toUint(16);
    udat.Data4[7] = str.mid(34, 2).toUint(16);
    memcpy(fData, &udat, sizeof(fData));
}
