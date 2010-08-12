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

DllClass plCameraModifier : public virtual plSingleModifier {
    CREATABLE(plCameraModifier, kCameraModifier, plSingleModifier)

public:
    DllClass CamTrans {
    protected:
        plKey fTransTo;
        bool fCutPos, fCutPOA, fIgnore;
        float fAccel, fDecel, fVelocity, fPOAAccel, fPOADecel, fPOAVelocity;

    public:
        CamTrans();

        void read(hsStream* S, plResManager* mgr);
        void write(hsStream* S, plResManager* mgr);
        void prcWrite(pfPrcHelper* prc);
        void prcParse(const pfPrcTag* tag, plResManager* mgr);
    };

protected:
    hsVector3 fFrom, fAt;
    plKey fBrain;
    hsTArray<CamTrans*> fTrans;
    float fFOVw, fFOVh;
    hsTArray<plMessage*> fMessageQueue;
    hsTArray<plKey> fSenderQueue;
    hsTArray<plCameraMsg*> fFOVInstructions;
    bool fAnimated, fStartAnimOnPush, fStopAnimOnPop, fResetAnimOnPop;

    void DeleteTrans();

public:
    plCameraModifier();
    virtual ~plCameraModifier();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void clearTrans();
    void clearMessageQueue();
    void clearFOVInstructions();
};

#endif
