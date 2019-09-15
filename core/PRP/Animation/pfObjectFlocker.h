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

class PLASMA_DLL pfObjectFlocker : public plSingleModifier
{
    CREATABLE(pfObjectFlocker, kObjectFlocker, plSingleModifier)

public:
    struct PLASMA_DLL pfFlock
    {
        float fGoalWeight, fRandomWeight;
        float fSeparationWeight, fSeparationRadius;
        float fCohesionWeight, fCohesionRadius;
        float fMaxForce, fMaxSpeed, fMinSpeed;

        pfFlock()
            : fGoalWeight(8.0f), fRandomWeight(12.0f), fSeparationWeight(12.0f),
              fSeparationRadius(5.0f), fCohesionWeight(8.0f),
              fCohesionRadius(9.0f), fMaxForce(10.0f), fMaxSpeed(5.0f),
              fMinSpeed(4.0f) { }
    };

protected:
    unsigned char fNumBoids;
    bool fUseTargetRotation, fRandomizeAnimationStart;
    plKey fBoidKey;
    pfFlock fFlock;

public:
    pfObjectFlocker()
        : fNumBoids(), fUseTargetRotation(), fRandomizeAnimationStart() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned char getNumBoids() const { return fNumBoids; }
    bool getUseTargetRotation() const { return fUseTargetRotation; }
    bool getRandomizeAnimationStart() const { return fRandomizeAnimationStart; }
    plKey getBoidKey() const { return fBoidKey; }

    void setNumBoids(unsigned char boids) { fNumBoids = boids; }
    void setUseTargetRotation(bool use) { fUseTargetRotation = use; }
    void setRandomizeAnimationStart(bool randomize) { fRandomizeAnimationStart = randomize; }
    void setBoidKey(plKey boidKey) { fBoidKey = std::move(boidKey); }

    pfFlock& getFlock() { return fFlock; }
    const pfFlock& getFlock() const { return fFlock; }
};

#endif
