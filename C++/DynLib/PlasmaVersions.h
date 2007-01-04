#ifndef _PLASMA_VERSIONS_H
#define _PLASMA_VERSIONS_H

#define PLS_MAJ_URU     63
#define PLS_MAJ_LIVE    69
#define PLS_MIN_PRIME   11
#define PLS_MIN_POTS    12
#define PLS_MIN_LIVE2    2
#define PLS_MIN_LIVE3    3

#define PRP_URU 5
#define PRP_EOA 6

enum PlasmaVer {
    pvUnknown = 0,
    pvPrime = 1,
    pvPots = 2,
    pvEoa = 3,
    pvLive = 4
};

#endif
