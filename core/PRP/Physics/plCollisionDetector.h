#ifndef _PLCOLLISIONDETECTOR_H
#define _PLCOLLISIONDETECTOR_H

#include "plDetectorModifier.h"

DllClass plCollisionDetector : public plDetectorModifier {
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
    virtual ~plCollisionDetector();

    DECLARE_CREATABLE(plCollisionDetector)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned char getType() const;
    void setType(unsigned char type);
};

DllClass plSubworldRegionDetector : public plCollisionDetector {
protected:
    plKey fSub;
    bool fOnExit;

public:
    plSubworldRegionDetector();
    virtual ~plSubworldRegionDetector();

    DECLARE_CREATABLE(plSubworldRegionDetector)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getSubworld() const;
    bool getOnExit() const;

    void setSubworld(plKey subworld);
    void setOnExit(bool onExit);
};

DllClass plPanicLinkRegion : public plCollisionDetector {
protected:
    bool fPlayLinkOutAnim;

public:
    plPanicLinkRegion();
    virtual ~plPanicLinkRegion();

    DECLARE_CREATABLE(plPanicLinkRegion)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getPlayLinkOutAnim() const;
    void setPlayLinkOutAnim(bool play);
};

#endif
