#ifndef _PLASMA_VERSIONS_H
#define _PLASMA_VERSIONS_H

#define PLS_MAJ_URU     63
#define PLS_MAJ_LIVE    70
#define PLS_MIN_PRIME   11
#define PLS_MIN_POTS    12

#define PRP_URU 5
#define PRP_EOA 6

enum PlasmaVer {
    pvUnknown = 0,
    pvPrime = 0x02006311,
    pvPots = 0x02006312,
    pvLive = 0x02007000,
    pvEoa = 0x02010000,
    pvHex = 0x03000000,
};

#endif
