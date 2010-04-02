#include "pnClient.h"

hsUint32 pnClient::nextTransId() {
    static hsUint32 s_transId = 0;
    static hsMutex s_tidMutex;

    s_tidMutex.lock();
    hsUint32 tid = ++s_transId;
    s_tidMutex.unlock();
    return tid;
}
