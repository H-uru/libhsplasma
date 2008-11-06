#ifndef _PLLAYERMOVIE_H
#define _PLLAYERMOVIE_H

#include "plLayerAnimation.h"

DllClass plLayerMovie : public plLayerAnimation {
protected:
    plString fMovieName;

public:
    plLayerMovie();
    virtual ~plLayerMovie();

    DECLARE_CREATABLE(plLayerMovie)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getMovieName() const;
    void setMovieName(const plString& name);
};

DllClass plLayerAVI : public plLayerMovie {
public:
    DECLARE_CREATABLE(plLayerAVI)
};

DllClass plLayerBink : public plLayerMovie {
public:
    DECLARE_CREATABLE(plLayerBink)
};

#endif
