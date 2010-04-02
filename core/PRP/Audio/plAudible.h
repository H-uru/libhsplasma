#ifndef _PLAUDIBLE_H
#define _PLAUDIBLE_H

#include "PRP/KeyedObject/hsKeyedObject.h"

DllClass plAudible : public hsKeyedObject {
    CREATABLE(plAudible, kAudible, hsKeyedObject)
};


DllClass plAudibleNull : public plAudible {
    CREATABLE(plAudibleNull, kAudibleNull, plAudible)
};


DllClass plWinAudible : public plAudible {
    CREATABLE(plWinAudible, kWinAudible, plAudible)

private:
    hsTArray<plKey> fSoundObjs;
    plKey fSceneNode;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getSounds() const { return fSoundObjs; }
    hsTArray<plKey>& getSounds() { return fSoundObjs; }
    void addSound(plKey sound) { fSoundObjs.append(sound); }
    void delSound(size_t idx) { fSoundObjs.remove(idx); }
    void clearSounds() { fSoundObjs.clear(); }

    plKey getSceneNode() const { return fSceneNode; }
    void setSceneNode(plKey node) { fSceneNode = node; }
};


DllClass pl2WayWinAudible : public plWinAudible {
    CREATABLE(pl2WayWinAudible, k2WayWinAudible, plWinAudible)
};

#endif
