#include <cstdio>
#include <cstring>
#include "ResManager/pdUnifiedTypeMap.h"

#define MAX_KEYED       0x0170
#define MAX_NONKEYED    0x03E7
#define MAX_POSTDB      0x04E5

#define P2M(i, ver) pdUnifiedTypeMap::PlasmaToMapped(i, ver)
#define M2P(i, ver) pdUnifiedTypeMap::MappedToPlasma(i, ver)


void GetIdxStr(char* str, short idx) {
    if (idx == -1)
        snprintf(str, 5, "----");
    else
        snprintf(str, 5, "%04hX", idx);
}

void PrintInfo(short clsIdx) {
    char PrimeIdx[5], PotsIdx[5], LiveIdx[5], EoaIdx[5], HexIdx[5];
    GetIdxStr(PrimeIdx, pdUnifiedTypeMap::MappedToPlasma(clsIdx, PlasmaVer::pvPrime));
    GetIdxStr(PotsIdx, pdUnifiedTypeMap::MappedToPlasma(clsIdx, PlasmaVer::pvPots));
    GetIdxStr(LiveIdx, pdUnifiedTypeMap::MappedToPlasma(clsIdx, PlasmaVer::pvMoul));
    GetIdxStr(EoaIdx, pdUnifiedTypeMap::MappedToPlasma(clsIdx, PlasmaVer::pvEoa));
    GetIdxStr(HexIdx, pdUnifiedTypeMap::MappedToPlasma(clsIdx, PlasmaVer::pvHex));
    printf("x%04hX U[%s] P[%s] L[%s] E[%s] H[%s] %s\n", clsIdx,
           PrimeIdx, PotsIdx, LiveIdx, EoaIdx, HexIdx,
           pdUnifiedTypeMap::ClassName(clsIdx));
}

bool TestMap(short idx, PlasmaVer ver) {
    if (idx != P2M(M2P(idx, ver), ver) && M2P(idx, ver) != -1) {
        printf("[%04hX] %s : %04hX -> %04hX -> %04hX\n", idx,
               pdUnifiedTypeMap::ClassName(idx),
               idx, M2P(idx, ver), P2M(M2P(idx, ver), ver));
        return false;
    } else {
        return true;
    }
}

int main(int argc, char** argv) {
    if ((argc > 1) && (strcmp(argv[1], "-test") == 0)) {
        bool clean = true;

        /* Print mismatched types */
        for (short i=0x0000; i<TYPESPACE_MAX; i++) {
            clean &= TestMap(i, PlasmaVer::pvPrime);
            clean &= TestMap(i, PlasmaVer::pvPots);
            clean &= TestMap(i, PlasmaVer::pvMoul);
            clean &= TestMap(i, PlasmaVer::pvEoa);
            clean &= TestMap(i, PlasmaVer::pvHex);
        }

        if (clean)
            printf("No errors detected!\n");
    } else if ((argc > 1) && (strcmp(argv[1], "-live") == 0)) {
        for (short i=0x0000; i<=MAX_KEYED; i++) {
            short id = pdUnifiedTypeMap::MappedToPlasma(i, PlasmaVer::pvMoul);
            if (id >= 0)
                printf("%04hX %s\n", id, pdUnifiedTypeMap::ClassName(id, PlasmaVer::pvMoul));
        }
        for (short i=0x0200; i<=MAX_NONKEYED; i++) {
            short id = pdUnifiedTypeMap::MappedToPlasma(i, PlasmaVer::pvMoul);
            if (id >= 0)
                printf("%04hX %s\n", id, pdUnifiedTypeMap::ClassName(id, PlasmaVer::pvMoul));
        }
        for (short i=0x0421; i<=MAX_POSTDB; i++) {
            short id = pdUnifiedTypeMap::MappedToPlasma(i, PlasmaVer::pvMoul);
            if (id >= 0)
                printf("%04hX %s\n", id, pdUnifiedTypeMap::ClassName(id, PlasmaVer::pvMoul));
        }
    } else {
        /* Print all types */
        for (short i=0x0000; i<=MAX_KEYED; i++)
            PrintInfo(i);
        for (short i=0x0200; i<=MAX_NONKEYED; i++)
            PrintInfo(i);
        for (short i=0x0421; i<=MAX_POSTDB; i++)
            PrintInfo(i);
    }

    return 0;
}
