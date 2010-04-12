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

#ifndef _PFOBJECTFLOCKER_H
#define _PFOBJECTFLOCKER_H

#include "PRP/Modifier/plModifier.h"

DllClass pfObjectFlocker : public plSingleModifier {
    CREATABLE(pfObjectFlocker, kObjectFlocker, plSingleModifier)

public:
    DllStruct pfFlock {
        float fGoalWeight, fRandomWeight;
        float fSeparationWeight, fSeparationRadius;
        float fCohesionWeight, fCohesionRadius;
        float fMaxForce, fMaxSpeed, fMinSpeed;

        pfFlock();
    };

protected:
    unsigned char fNumBoids;
    bool fUseTargetRotation, fRandomizeAnimationStart;
    plKey fBoidKey;
    pfFlock fFlock;

public:
    pfObjectFlocker();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned char getNumBoids() const { return fNumBoids; }
    bool getUseTargetRotation() const { return fUseTargetRotation; }
    bool getRandomizeAnimationStart() const { return fRandomizeAnimationStart; }
    plKey getBoidKey() const { return fBoidKey; }

    void setNumBoids(unsigned char boids) { fNumBoids = boids; }
    void setUseTargetRotation(bool use) { fUseTargetRotation = use; }
    void setRandomizeAnimationStart(bool randomize) { fRandomizeAnimationStart = randomize; }
    void setBoidKey(plKey boidKey) { fBoidKey = boidKey; }

    pfFlock& getFlock() { return fFlock; }
};

#endif
