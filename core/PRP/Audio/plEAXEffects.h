#ifndef _PLEAXEFFECTS_H
#define _PLEAXEFFECTS_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllClass plEAXSourceSoftSettings {
protected:
    short fOcclusion;
    float fOcclusionLFRatio, fOcclusionRoomRatio, fOcclusionDirectRatio;

public:
    plEAXSourceSoftSettings();
    void reset();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    short getOcclusion() const;
    float getLFRatio() const;
    float getRoomRatio() const;
    float getDirectRatio() const;

    void setOcclusion(short occlusion);
    void setLFRatio(float ratio);
    void setRoomRatio(float ratio);
    void setDirectRatio(float ratio);
};

DllClass plEAXSourceSettings {
protected:
    short fRoom, fRoomHF;
    bool fEnabled, fRoomAuto, fRoomHFAuto;
    short fOutsideVolHF;
    float fAirAbsorptionFactor, fRoomRolloffFactor;
    float fDopplerFactor, fRolloffFactor;
    plEAXSourceSoftSettings fSoftStarts, fSoftEnds;
    float fOcclusionSoftValue;

public:
    plEAXSourceSettings();

    void enable(bool en);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    bool isEnabled() const;
    short getRoom() const;
    short getRoomHF() const;
    bool getRoomAuto() const;
    bool getRoomHFAuto() const;
    short getOutsideVolHF() const;
    float getAirAbsorptionFactor() const;
    float getRoomRolloffFactor() const;
    float getDopplerFactor() const;
    float getRolloffFactor() const;
    float getOcclusionSoftValue() const;

    void setRoom(short room);
    void setRoomHF(short room);
    void setRoomAuto(bool aut);
    void setRoomHFAuto(bool aut);
    void setOutsideVolHF(short vol);
    void setAirAbsorptionFactor(float factor);
    void setRoomRolloffFactor(float factor);
    void setDopplerFactor(float factor);
    void setRolloffFactor(float factor);
    void setOcclusionSoftValue(float value);

    plEAXSourceSoftSettings& getSoftStarts();
    plEAXSourceSoftSettings& getSoftEnds();
};

#endif
