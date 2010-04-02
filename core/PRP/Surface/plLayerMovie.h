#ifndef _PLLAYERMOVIE_H
#define _PLLAYERMOVIE_H

#include "plLayerAnimation.h"

DllClass plLayerMovie : public plLayerAnimation {
    CREATABLE(plLayerMovie, kLayerMovie, plLayerAnimation)

protected:
    plString fMovieName;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getMovieName() const { return fMovieName; }
    void setMovieName(const plString& name) { fMovieName = name; }
};


DllClass plLayerAVI : public plLayerMovie {
    CREATABLE(plLayerAVI, kLayerAVI, plLayerMovie)
};


DllClass plLayerBink : public plLayerMovie {
    CREATABLE(plLayerBink, kLayerBink, plLayerMovie)
};

#endif
