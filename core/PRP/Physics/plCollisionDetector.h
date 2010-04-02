#ifndef _PLCOLLISIONDETECTOR_H
#define _PLCOLLISIONDETECTOR_H

#include "plDetectorModifier.h"

DllClass plCollisionDetector : public plDetectorModifier {
    CREATABLE(plCollisionDetector, kCollisionDetector, plDetectorModifier)

public:
    enum {
        kTypeEnter = 0x1,
        kTypeExit = 0x2,
        kTypeAny = 0x4,
        kTypeUnEnter = 0x8,
        kTypeUnExit = 0x10,
        kTypeBump = 0x20
    };

protected:
    unsigned char fType;

public:
    plCollisionDetector();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned char getType() const { return fType; }
    void setType(unsigned char type) { fType = type; }
};


DllClass plSubworldRegionDetector : public plCollisionDetector {
    CREATABLE(plSubworldRegionDetector, kSubworldRegionDetector,
              plCollisionDetector)

protected:
    plKey fSub;
    bool fOnExit;

public:
    plSubworldRegionDetector();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getSubworld() const { return fSub; }
    bool getOnExit() const { return fOnExit; }

    void setSubworld(plKey subworld) { fSub = subworld; }
    void setOnExit(bool onExit) { fOnExit = onExit; }
};


DllClass plPanicLinkRegion : public plCollisionDetector {
    CREATABLE(plPanicLinkRegion, kPanicLinkRegion, plCollisionDetector)

protected:
    bool fPlayLinkOutAnim;

public:
    plPanicLinkRegion();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getPlayLinkOutAnim() const { return fPlayLinkOutAnim; }
    void setPlayLinkOutAnim(bool play) { fPlayLinkOutAnim = play; }
};

#endif
