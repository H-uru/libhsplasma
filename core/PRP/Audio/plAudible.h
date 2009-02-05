#ifndef _PLAUDIBLE_H
#define _PLAUDIBLE_H

#include "PRP/KeyedObject/hsKeyedObject.h"

DllClass plAudible : public hsKeyedObject {
public:
    plAudible();
    virtual ~plAudible();

    DECLARE_CREATABLE(plAudible)
};

DllClass plAudibleNull : public plAudible {
public:
    plAudibleNull();
    virtual ~plAudibleNull();

    DECLARE_CREATABLE(plAudibleNull)
};

DllClass plWinAudible : public plAudible {
protected:
    hsTArray<plKey> fSoundObjs;
    plKey fSceneNode;

public:
    plWinAudible();
    virtual ~plWinAudible();

    DECLARE_CREATABLE(plWinAudible)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumSounds() const;
    plKey getSound(size_t idx) const;
    void addSound(plKey sound);
    void delSound(size_t idx);
    void clearSounds();

    plKey getSceneNode() const;
    void setSceneNode(plKey node);
};

DllClass pl2WayWinAudible : public plWinAudible {
public:
    pl2WayWinAudible();
    virtual ~pl2WayWinAudible();

    DECLARE_CREATABLE(pl2WayWinAudible)
};

#endif
