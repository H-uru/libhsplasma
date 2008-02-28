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

plUUID::plUUID(const char* str) {
    FromString(str);
}
*/

void plUUID::read(hsStream* S) {
    S->read(16, fData);
}

void plUUID::write(hsStream* S) {
    S->write(16, fData);
}

void plUUID::prcWrite(pfPrcHelper* prc) {
    prc->writeTagNoBreak("plUUID");
    prc->getStream()->writeStr(toString());
    prc->closeTagNoBreak();
}

void plUUID::clear() {
    memset(fData, 0, sizeof(fData));
}

plString plUUID::toString() const {
    struct WinUUID {
        unsigned int Data1;
        unsigned short Data2, Data3;
        unsigned char Data4[8];
    };
    WinUUID udat;
    memcpy(&udat, fData, sizeof(WinUUID));
    return plString::Format("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
             udat.Data1, udat.Data2, udat.Data3,
             udat.Data4[0], udat.Data4[1], udat.Data4[2], udat.Data4[3],
             udat.Data4[4], udat.Data4[5], udat.Data4[6], udat.Data4[7]);
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
