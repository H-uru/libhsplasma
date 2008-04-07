#ifndef _PLASMA_VERSIONS_H
#define _PLASMA_VERSIONS_H

/* These MUST remain in order for version matching to work */
enum PlasmaVer {
    pvUnknown   = 0,
    pvPrime     = 0x02006311,   // 2.0 r63.11
    pvPots      = 0x02006312,   // 2.0 r63.12
    pvLive      = 0x02007000,   // 2.0 r70
    pvEoa       = 0x02010610,   // 2.1 r6.10
    pvHex       = 0x03000000,   // 3.0
};

const char* GetVersionName(PlasmaVer ver);

#endif
