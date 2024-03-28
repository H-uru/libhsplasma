// Subset of 3rdPartyLibs/AL/EFX-Util.h containing only the structures
// used in the public API of plEAXListenerMod.

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
    unsigned long ulEnvironment;
    float flEnvironmentSize;
    float flEnvironmentDiffusion;
    long lRoom;
    long lRoomHF;
    long lRoomLF;
    float flDecayTime;
    float flDecayHFRatio;
    float flDecayLFRatio;
    long lReflections;
    float flReflectionsDelay;
    EAXVECTOR vReflectionsPan;
    long lReverb;
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
    unsigned long ulFlags;
} EAXREVERBPROPERTIES, *LPEAXREVERBPROPERTIES;
#endif
