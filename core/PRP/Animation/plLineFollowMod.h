#ifndef _PLLINEFOLLOWMOD_H
#define _PLLINEFOLLOWMOD_H

#include "PRP/Modifier/plModifier.h"
#include "plAnimPath.h"

DllClass plLineFollowMod : public plMultiModifier {
public:
    enum FollowMode {
        kFollowObject, kFollowListener, kFollowCamera, kFollowLocalAvatar
    };

    enum {
        kNone = 0,
        kFullMatrix = 0x1,
        kOffsetFeet = 0x2,
        kOffsetAng = 0x4,
        kOffset = kOffsetFeet | kOffsetAng,
        kOffsetClamp = 0x8,
        kForceToLine = 0x10,
        kSpeedClamp = 0x20,
        kSearchPopPos = 0x40
    };

protected:
    FollowMode fFollowMode;
    unsigned short fFollowFlags;
    plAnimPath* fPath;
    plKey fPathParent, fRefObj;
    hsTArray<plKey> fStereizers;
    float fOffset, fOffsetClamp, fSpeedClamp;

public:
    plLineFollowMod();
    virtual ~plLineFollowMod();

    DECLARE_CREATABLE(plLineFollowMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    FollowMode getFollowMode() const;
    unsigned short getFollowFlags() const;
    plAnimPath* getPath() const;
    plKey getPathParent() const;
    plKey getRefObj() const;
    float getOffset() const;
    float getOffsetClamp() const;
    float getSpeedClamp() const;

    void setFollowMode(FollowMode mode);
    void setFollowFlags(unsigned short flags);
    void setPath(plAnimPath* path);
    void setPathParent(plKey parent);
    void setRefObj(plKey obj);
    void setOffset(float offset);
    void setOffsetClamp(float clamp);
    void setSpeedClamp(float clamp);

    size_t getNumStereizers() const;
    plKey getStereizer(size_t idx) const;
    void addStereizer(plKey stereizer);
    void delStereizer(size_t idx);
    void clearStereizers();
};

DllClass plRailCameraMod : public plLineFollowMod {
public:
    plRailCameraMod();
    virtual ~plRailCameraMod();

    DECLARE_CREATABLE(plRailCameraMod)
};

#endif
