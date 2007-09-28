#include "plSound.h"
#include "../plResMgr/plResManager.h"

/* plSound::plFadeParams */
plSound::plFadeParams::plFadeParams()
       : fLengthInSecs(0), fVolStart(0.0f), fVolEnd(0.0f), fType(kLinear),
         fStopWhenDone(0), fFadeSoftVol(0), fCurrTime(0.0f) { }

void plSound::plFadeParams::read(hsStream* S) {
    fLengthInSecs = S->readFloat();
    fVolStart = S->readFloat();
    fVolEnd = S->readFloat();
    fType = S->readByte();
    fCurrTime = S->readFloat();
    fStopWhenDone = S->readInt();
    fFadeSoftVol = S->readInt();
}

void plSound::plFadeParams::write(hsStream* S) {
    S->writeFloat(fLengthInSecs);
    S->writeFloat(fVolStart);
    S->writeFloat(fVolEnd);
    S->writeByte(fType);
    S->writeFloat(fCurrTime);
    S->writeInt(fStopWhenDone);
    S->writeInt(fFadeSoftVol);
}

void plSound::plFadeParams::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plFadeParams");
    prc->writeParam("type", fType);
    prc->writeParam("length", fLengthInSecs);
    prc->writeParam("start", fVolStart);
    prc->writeParam("end", fVolEnd);
    prc->writeParam("current", fCurrTime);
    prc->writeParam("StopWhenDone", fStopWhenDone);
    prc->writeParam("FadeSoftVol", fFadeSoftVol);
    prc->endTag(true);
}

/* plSound */
bool plSound::fLoadOnDemandFlag = true;
bool plSound::fLoadFromDiskOnDemandFlag = true;

plSound::plSound()
       : fPlaying(false), fActive(false), fTime(0.0f), fMaxFalloff(0),
         fMinFalloff(0), fCurrVolume(0.0f), fOuterVol(0), fInnerCone(360),
         fOuterCone(360), fLength(0.0f), fDesiredVol(0.0f), fFadedVolume(0.0f),
         fProperties(0), fType(kStartType), fPriority(0), fMuted(true),
         fFading(false), fRegisteredForTime(false), fPlayOnReactivate(false),
         fNotHighEnoughPriority(false), fOwningSceneObject(NULL),
         fQueued(false), fCurrFadeParams(NULL), fSoftRegion(NULL),
         fSoftVolume(0.0f), fDistAttenuation(0.0f), fVirtualStartTime(0.0f),
         fRegistered(false), fRefIndex(-1), fSoftOcclusionRegion(NULL),
         fDataBuffer(NULL), fDataBufferLoaded(false), fLoading(false) { }

plSound::~plSound() { }

IMPLEMENT_CREATABLE(plSound, kSound, plSynchedObject)

void plSound::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);
    IRead(S, mgr);

    //if (fProperties & kPropAutoStart)
    //    Play();
    if (fProperties & kPropLocalOnly)
        fSynchFlags |= kLocalOnly;
    if (fPlaying)
        fFading = (fFadeInParams.fLengthInSecs > 0.0f);
    //if (fLoadOnDemandFlag && !(fProperties & kPropDisableLOD)) {
    //    if (fLoadFromDiskOnDemand) return;
    //    if (fProperties & kPropLoadOnlyOnCall) return;
    //    if (fPriority > plgAudioSys::fPriorityCutoff) return;
    //    IPreLoadBuffer();
    //} else {
    //    LoadSound(fProperties & kPropIs3DSound);
    //}
}

void plSound::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);
    IWrite(S, mgr);
}

void plSound::IRead(hsStream* S, plResManager* mgr) {
    fPlaying = S->readBool();
    //fVirtualStartTime = hsTimer::GetTheTimer()->fSysSeconds;
    fTime = S->readDouble();
    fMaxFalloff = S->readInt();
    fMinFalloff = S->readInt();
    fCurrVolume = S->readFloat();
    fDesiredVol = S->readFloat();
    if (fDesiredVol > 1.0f) fDesiredVol = 1.0f;
    if (fCurrVolume > 1.0f) fCurrVolume = 1.0f;
    fOuterVol = S->readInt();
    fInnerCone = S->readInt();
    fOuterCone = S->readInt();
    fFadedVolume = S->readFloat();
    fProperties = S->readInt();
    fType = S->readByte();
    fPriority = S->readByte();

    if (fPlaying)
        fProperties |= kPropAutoStart;
    fFadeInParams.read(S);
    fFadeOutParams.read(S);

    fSoftRegion = mgr->readKey(S);
    fDataBuffer = mgr->readKey(S);
    fEAXSettings.read(S);
    fSoftOcclusionRegion = mgr->readKey(S);
}

void plSound::IWrite(hsStream* S, plResManager* mgr) {
    S->writeBool(fPlaying);
    S->writeDouble(fTime);
    S->writeInt(fMaxFalloff);
    S->writeInt(fMinFalloff);
    S->writeFloat(fCurrVolume);
    S->writeFloat(fDesiredVol);
    S->writeInt(fOuterVol);
    S->writeInt(fInnerCone);
    S->writeInt(fOuterCone);
    S->writeFloat(fFadedVolume);
    S->writeInt(fProperties);
    S->writeByte(fType);
    S->writeByte(fPriority);

    fFadeInParams.write(S);
    fFadeOutParams.write(S);
    mgr->writeKey(S, fSoftRegion);
    mgr->writeKey(S, fDataBuffer);
    fEAXSettings.write(S);
    mgr->writeKey(S, fSoftOcclusionRegion);
}

void plSound::prcWrite(pfPrcHelper* prc) {
    plSynchedObject::prcWrite(prc);

    prc->startTag("Params");
      prc->writeParam("Playing", fPlaying);
      prc->writeParam("Time", fTime);
      prc->writeParam("MaxFalloff", fMaxFalloff);
      prc->writeParam("MinFalloff", fMinFalloff);
      prc->writeParam("Properties", fProperties);
      prc->writeParam("Type", fType);
      prc->writeParam("Priority", fPriority);
    prc->endTag(true);
    prc->startTag("Volumes");
      prc->writeParam("Current", fCurrVolume);
      prc->writeParam("Desired", fDesiredVol);
      prc->writeParam("Fade", fFadedVolume);
    prc->endTag(true);
    prc->startTag("Cone");
      prc->writeParam("OuterVol", fOuterVol);
      prc->writeParam("InnerCone", fInnerCone);
      prc->writeParam("OuterCone", fOuterCone);
    prc->endTag(true);

    prc->writeSimpleTag("FadeInParams");
      fFadeInParams.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("FadeOutParams");
      fFadeOutParams.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SoftRegion");
      fSoftRegion->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("DataBuffer");
      fDataBuffer->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SoftOcclusionRegion");
      fSoftOcclusionRegion->prcWrite(prc);
    prc->closeTag();

    fEAXSettings.prcWrite(prc);
}
