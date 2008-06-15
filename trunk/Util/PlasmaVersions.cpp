#include "PlasmaVersions.h"

const char* GetVersionName(PlasmaVer ver) {
    switch (ver) {
    case pvChoru:
        return "Choru Beta";
    case pvPrime:
        return "Prime/UU";
    case pvPots:
        return "PotS/CC";
    case pvLive:
        return "MOUL";
    case pvEoa:
        return "Myst V/Crowthistle";
    case pvHex:
        return "Hex Isle";
    default:
        return "Unknown";
    }
}
