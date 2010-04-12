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

#ifndef _PLAVBRAINGENERIC_H
#define _PLAVBRAINGENERIC_H

#include "plArmatureBrain.h"
#include "plAnimStage.h"
#include "plAGAnim.h"
#include "PRP/Message/plMessage.h"

DllClass plAvBrainGeneric : public plArmatureBrain {
    CREATABLE(plAvBrainGeneric, kAvBrainGeneric, plArmatureBrain)

public:
    enum BrainType {
        kGeneric, kLadder, kSit, kEmote, kAFK, kNumBrainTypes,
        kNonGeneric = kNumBrainTypes
    };

    enum ExitFlag {
        kExitNormal   = 0,
        kExitAnyTask  = 0x1,
        kExitNewBrain = 0x2,
        kExitAnyInput = 0x4,
        kExitMaxFlag  = 0x8,
    };

    enum MoveMode {
        kMoveAbsolute, kMoveRelative, kMoveNormal, kMoveStandstill,
        kMaxMoveMode
    };

    enum Mode {
        kEntering = 1, kNormal, kFadingIn, kFadingOut, kExit, kAbort,
        kMaxMode
    };

private:
    hsTArray<plAnimStage*> fStages;
    int fCurStage;
    BrainType fType;
    unsigned int fExitFlags;
    Mode fMode;
    bool fForward;
    plMessage* fStartMessage;
    plMessage* fEndMessage;
    float fFadeIn, fFadeOut;
    MoveMode fMoveMode;
    plAGAnim::BodyUsage fBodyUsage;
    plKey fRecipient;

public:
    plAvBrainGeneric();
    virtual ~plAvBrainGeneric();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plAnimStage*>& getStages() const { return fStages; }
    hsTArray<plAnimStage*>& getStages() { return fStages; }
    void addStage(plAnimStage* stage) { fStages.append(stage); }
    void delStage(size_t idx);
    void clearStages();

    int getCurStage() const { return fCurStage; }
    BrainType getType() const { return fType; }
    unsigned int getExitFlags() const { return fExitFlags; }
    Mode getMode() const { return fMode; }
    bool isForward() const { return fForward; }
    plMessage* getStartMessage() const { return fStartMessage; }
    plMessage* getEndMessage() const { return fEndMessage; }
    float getFadeIn() const { return fFadeIn; }
    float getFadeOut() const { return fFadeOut; }
    MoveMode getMoveMode() const { return fMoveMode; }
    plAGAnim::BodyUsage getBodyUsage() const { return fBodyUsage; }
    plKey getRecipient() const { return fRecipient; }

    void setCurStage(int stage) { fCurStage = stage; }
    void setType(BrainType type) { fType = type; }
    void setExitFlags(unsigned int flags) { fExitFlags = flags; }
    void setMode(Mode mode) { fMode = mode; }
    void setForward(bool fwd) { fForward = fwd; }
    void setFadeIn(float fade) { fFadeIn = fade; }
    void setFadeOut(float fade) { fFadeOut = fade; }
    void setMoveMode(MoveMode mode) { fMoveMode = mode; }
    void setBodyUsage(plAGAnim::BodyUsage usage) { fBodyUsage = usage; }
    void setRecipient(plKey recp) { fRecipient = recp; }
    void setStartMessage(plMessage* msg);
    void setEndMessage(plMessage* msg);
};

#endif
