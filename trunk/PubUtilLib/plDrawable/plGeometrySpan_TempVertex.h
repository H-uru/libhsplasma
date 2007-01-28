#ifndef _PLGEOMETRYSPAN_TEMPVERTEX_H
#define _PLGEOMETRYSPAN_TEMPVERTEX_H

struct TempVertex {
    hsPoint3    fPosition;      // +0
    hsPoint3    fNormal;        // +0C
    unsigned int      fColor;         // +18
    unsigned int      fSpecularColor; // +1C
    hsColorRGBA fMultColor;     // +20
    hsColorRGBA fAddColor;      // +30
    hsPoint3[8] fUVs;           // +40
    float[3]    fWeights;       // +A0
    unsigned int      fIndices        // +AC
};

#endif