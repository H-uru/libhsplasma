#ifndef _PLATCEASECURVES_H
#define _PLATCEASECURVES_H

#include "PRP/plCreatable.h"

DllClass plATCEaseCurve : public plCreatable {
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


DllClass plSplineEaseCurve : public plATCEaseCurve {
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


DllClass plConstAccelEaseCurve : public plATCEaseCurve {
    CREATABLE(plConstAccelEaseCurve, kConstAccelEaseCurve, plATCEaseCurve)
};

#endif
