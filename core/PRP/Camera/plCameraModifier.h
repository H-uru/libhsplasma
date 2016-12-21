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
    virtual ~plCameraModifier();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    void clearTrans();
    void clearMessageQueue();
    void clearFOVInstructions();
};

#endif
