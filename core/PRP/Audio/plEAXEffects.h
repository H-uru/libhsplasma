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
    short getOcclusion() const { return fOcclusion; }
    float getLFRatio() const { return fOcclusionLFRatio; }
    float getRoomRatio() const { return fOcclusionRoomRatio; }
    float getDirectRatio() const { return fOcclusionDirectRatio; }

    void setOcclusion(short occlusion) { fOcclusion = occlusion; }
    void setLFRatio(float ratio) { fOcclusionLFRatio = ratio; }
    void setRoomRatio(float ratio) { fOcclusionRoomRatio = ratio; }
    void setDirectRatio(float ratio) { fOcclusionDirectRatio = ratio; }
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
    bool isEnabled() const { return fEnabled; }
    short getRoom() const { return fRoom; }
    short getRoomHF() const { return fRoomHF; }
    bool getRoomAuto() const { return fRoomAuto; }
    bool getRoomHFAuto() const { return fRoomHFAuto; }
    short getOutsideVolHF() const { return fOutsideVolHF; }
    float getAirAbsorptionFactor() const { return fAirAbsorptionFactor; }
    float getRoomRolloffFactor() const { return fRoomRolloffFactor; }
    float getDopplerFactor() const { return fDopplerFactor; }
    float getRolloffFactor() const { return fRolloffFactor; }
    float getOcclusionSoftValue() const { return fOcclusionSoftValue; }

    void setRoom(short room) { fRoom = room; }
    void setRoomHF(short roomHF) { fRoomHF = roomHF; }
    void setRoomAuto(bool aut) { fRoomAuto = aut; }
    void setRoomHFAuto(bool aut) { fRoomHFAuto = aut; }
    void setOutsideVolHF(short vol) { fOutsideVolHF = vol; }
    void setAirAbsorptionFactor(float factor) { fAirAbsorptionFactor = factor; }
    void setRoomRolloffFactor(float factor) { fRoomRolloffFactor = factor; }
    void setDopplerFactor(float factor) { fDopplerFactor = factor; }
    void setRolloffFactor(float factor) { fRolloffFactor = factor; }
    void setOcclusionSoftValue(float value) { fOcclusionSoftValue = value; }

    const plEAXSourceSoftSettings& getSoftStarts() const { return fSoftStarts; }
    plEAXSourceSoftSettings& getSoftStarts() { return fSoftStarts; }
    const plEAXSourceSoftSettings& getSoftEnds() const { return fSoftEnds; }
    plEAXSourceSoftSettings& getSoftEnds() { return fSoftEnds; }
};

#endif
