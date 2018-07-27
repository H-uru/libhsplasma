/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLCAMERAMODIFIER_H
#define _PLCAMERAMODIFIER_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Message/plCameraMsg.h"
#include <tuple>

class PLASMA_DLL plCameraModifier : public plSingleModifier {
    CREATABLE(plCameraModifier, kCameraModifier, plSingleModifier)

public:
    class PLASMA_DLL CamTrans {
    protected:
        plKey fTransTo;
        bool fCutPos, fCutPOA, fIgnore;
        float fAccel, fDecel, fVelocity, fPOAAccel, fPOADecel, fPOAVelocity;

    public:
        CamTrans() : fCutPos(false), fCutPOA(false), fIgnore(false), fAccel(60.0f),
                     fDecel(60.0f), fVelocity(60.0f), fPOAAccel(60.0f),
                     fPOADecel(60.0f), fPOAVelocity(60.0f) { }

        void read(hsStream* S, plResManager* mgr);
        void write(hsStream* S, plResManager* mgr);
        void prcWrite(pfPrcHelper* prc);
        void prcParse(const pfPrcTag* tag, plResManager* mgr);

    public:
        plKey getTransTo() const { return fTransTo; }
        bool getCutPos() const { return fCutPos; }
        bool getCutPOA() const { return fCutPOA; }
        bool getIgnore() const { return fIgnore; }
        float getAccel() const { return fAccel; }
        float getDecel() const { return fDecel; }
        float getVelocity() const { return fVelocity; }
        float getPOAAccel() const { return fPOAAccel; }
        float getPOADecel() const { return fPOADecel; }
        float getPOAVelocity() const { return fPOAVelocity; }

        void setTransTo(const plKey& transTo) { fTransTo = transTo; }
        void setCutPos(bool cutPos) { fCutPos = cutPos; }
        void setCutPOA(bool cutPOA) { fCutPOA = cutPOA; }
        void setIgnore(bool ignore) { fIgnore = ignore; }
        void setAccel(float accel) { fAccel = accel; }
        void setDecel(float decel) { fDecel = decel; }
        void setVelocity(float velocity) { fVelocity = velocity; }
        void setPOAAccel(float poaAccel) { fPOAAccel = poaAccel; }
        void setPOADecel(float poaDecel) { fPOADecel = poaDecel; }
        void setPOAVelocity(float poaVelocity) { fPOAVelocity = poaVelocity; }
    };

protected:
    hsVector3 fFrom, fAt;
    plKey fBrain;
    std::vector<CamTrans*> fTrans;
    float fFOVw, fFOVh;
    std::vector<plMessage*> fMessageQueue;
    std::vector<plKey> fSenderQueue;
    std::vector<plCameraMsg*> fFOVInstructions;
    bool fAnimated, fStartAnimOnPush, fStopAnimOnPop, fResetAnimOnPop;

public:
    plCameraModifier() : fFrom(0.0f, 0.0f, 0.0f), fAt(0.0f, 1.0f, 0.0f),
                         fFOVw(45.0f), fFOVh(33.75f), fAnimated(false),
                         fStartAnimOnPush(false), fStopAnimOnPop(false),
                         fResetAnimOnPop(false) { }
    ~plCameraModifier() HS_OVERRIDE;

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

    bool orderAfter(const hsKeyedObject* other) const HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    hsVector3 getFrom() const { return fFrom; }
    hsVector3 getAt() const { return fAt; }
    plKey getBrain() const { return fBrain; }
    float getFOVw() const { return fFOVw; }
    float getFOVh() const { return fFOVh; }
    bool getAnimated() const { return fAnimated; }
    bool getStartAnimOnPush() const { return fStartAnimOnPush; }
    bool getStopAnimOnPop() const { return fStopAnimOnPop; }
    bool getResetAnimOnPop() const { return fResetAnimOnPop; }

    void setFrom(const hsVector3& from) { fFrom = from; }
    void setAt(const hsVector3& at) { fAt = at; }
    void setBrain(const plKey& brain) { fBrain = brain; }
    void setFOVw(float fovW) { fFOVw = fovW; }
    void setFOVh(float fovH) { fFOVh = fovH; }
    void setAnimated(bool animated) { fAnimated = animated; }
    void setStartAnimOnPush(bool startOnPush) { fStartAnimOnPush = startOnPush; }
    void setStopAnimOnPop(bool stopOnPop) { fStopAnimOnPop = stopOnPop; }
    void setResetAnimOnPop(bool resetOnPop) { fResetAnimOnPop = resetOnPop; }

    const std::vector<CamTrans*>& getTrans() const { return fTrans; }
    std::vector<CamTrans*>& getTrans() { return fTrans; }
    void addTrans(CamTrans* trans) { fTrans.push_back(trans); }
    void delTrans(size_t idx);
    void clearTrans();

    std::tuple<plMessage*, plKey> getMessage(size_t idx) {
        return std::make_tuple(fMessageQueue[idx], fSenderQueue[idx]);
    }

    void addMessage(plMessage* msg, const plKey& sender=plKey()) {
        fMessageQueue.push_back(msg);
        fSenderQueue.push_back(sender);
    }

    void delMessage(size_t idx);
    void clearMessageQueue();
    size_t getMessageQueueSize() const { return fMessageQueue.size(); }

    const std::vector<plCameraMsg*>& getFOVInstructions() const { return fFOVInstructions; }
    std::vector<plCameraMsg*>& getFOVInstructions() { return fFOVInstructions; }
    void addFOVInstruction(plCameraMsg* msg) { fFOVInstructions.push_back(msg); }
    void delFOVInstruction(size_t idx);
    void clearFOVInstructions();
};

#endif
