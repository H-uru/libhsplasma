#ifndef _PLATCEASECURVES_H
#define _PLATCEASECURVES_H

#include "PRP/plCreatable.h"

DllClass plATCEaseCurve : public plCreatable {
protected:
    float fStartSpeed, fMinLength, fMaxLength;
    double fBeginWorldTime;
    float fLength, fSpeed;

public:
    plATCEaseCurve();
    virtual ~plATCEaseCurve();

    DECLARE_CREATABLE(plATCEaseCurve)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getStartSpeed() const;
    float getSpeed() const;
    float getMinLength() const;
    float getMaxLength() const;
    float getLength() const;
    double getBeginWorldTime() const;

    void setStartSpeed(float speed);
    void setSpeed(float speed);
    void setLength(float length);
    void setLengthBounds(float min, float max);
    void setBeginWorldTime(double time);
};

DllClass plSplineEaseCurve : public plATCEaseCurve {
protected:
    float fCoef[4];

public:
    plSplineEaseCurve();
    virtual ~plSplineEaseCurve();

    DECLARE_CREATABLE(plSplineEaseCurve)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getSplineCoef(size_t idx) const;
    void setSplineCoef(size_t idx, float coef);
};

DllClass plConstAccelEaseCurve : public plATCEaseCurve {
public:
    plConstAccelEaseCurve();
    virtual ~plConstAccelEaseCurve();

    DECLARE_CREATABLE(plConstAccelEaseCurve)
};

#endif
