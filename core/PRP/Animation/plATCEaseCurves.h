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

#ifndef _PLATCEASECURVES_H
#define _PLATCEASECURVES_H

#include "PRP/plCreatable.h"

class PLASMA_DLL plATCEaseCurve : public plCreatable {
    CREATABLE(plATCEaseCurve, kATCEaseCurve, plCreatable)

private:
    float fStartSpeed, fMinLength, fMaxLength;
    double fBeginWorldTime;
    float fLength, fSpeed;

public:
    plATCEaseCurve();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getStartSpeed() const { return fStartSpeed; }
    float getSpeed() const { return fSpeed; }
    float getMinLength() const { return fMinLength; }
    float getMaxLength() const { return fMaxLength; }
    float getLength() const { return fLength; }
    double getBeginWorldTime() const { return fBeginWorldTime; }

    void setStartSpeed(float speed) { fStartSpeed = speed; }
    void setSpeed(float speed) { fSpeed = speed; }
    void setLength(float length) { fLength = length; }
    void setLengthBounds(float min, float max) { fMinLength = min; fMaxLength = max; }
    void setBeginWorldTime(double time) { fBeginWorldTime = time; }
};


class PLASMA_DLL plSplineEaseCurve : public plATCEaseCurve {
    CREATABLE(plSplineEaseCurve, kSplineEaseCurve, plATCEaseCurve)

public:
    enum { kNumCoefficients = 4 };

private:
    float fCoef[4];

public:
    plSplineEaseCurve();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getSplineCoef(size_t idx) const { return fCoef[idx]; }
    void setSplineCoef(size_t idx, float coef) { fCoef[idx] = coef; }
};


class PLASMA_DLL plConstAccelEaseCurve : public plATCEaseCurve {
    CREATABLE(plConstAccelEaseCurve, kConstAccelEaseCurve, plATCEaseCurve)
};

#endif
