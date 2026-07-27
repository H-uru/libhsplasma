// Subset of 3rdPartyLibs/AL/EFX-Util.h containing only the structures
// used in the public API of plEAXListenerMod.

#include "PlasmaDefs.h"

#ifndef EAXVECTOR_DEFINED
#define EAXVECTOR_DEFINED
typedef struct _EAXVECTOR
{
    float x;
    float y;
    float z;
} EAXVECTOR;
#endif

#ifndef EAXREVERBPROPERTIES_DEFINED
#define EAXREVERBPROPERTIES_DEFINED
typedef struct _EAXREVERBPROPERTIES
{
    uint32_t ulEnvironment;
    float flEnvironmentSize;
    float flEnvironmentDiffusion;
    int32_t lRoom;
    int32_t lRoomHF;
    int32_t lRoomLF;
    float flDecayTime;
    float flDecayHFRatio;
    float flDecayLFRatio;
    int32_t lReflections;
    float flReflectionsDelay;
    EAXVECTOR vReflectionsPan;
    int32_t lReverb;
    float flReverbDelay;
    EAXVECTOR vReverbPan;
    float flEchoTime;
    float flEchoDepth;
    float flModulationTime;
    float flModulationDepth;
    float flAirAbsorptionHF;
    float flHFReference;
    float flLFReference;
    float flRoomRolloffFactor;
    uint32_t ulFlags;
} EAXREVERBPROPERTIES, *LPEAXREVERBPROPERTIES;
#endif
