#ifndef _PLAVSEEKMSG_H
#define _PLAVSEEKMSG_H

#include "plAvTaskMsg.h"
#include "Math/hsGeometry3.h"

DllClass plAvSeekMsg : public plAvTaskMsg {
public:
    enum Alignment {
        kAlignHandle, kAlignHandleAnimEnd, kAlignWorld, kAlignBone,
        kAlignBoneAnimEnd,
    };

    enum {
        kSeekFlagUnForce3rdPersonOnFinish = 0x1,
        kSeekFlagForce3rdPersonOnStart = 0x2,
        kSeekFlagNoWarpOnTimeout = 0x4,
        kSeekFlagRotationOnly = 0x8,
    };

private:
    plKey fSeekPoint;
    hsVector3 fTargetPos, fTargetLookAt;
    float fDuration;
    bool fSmartSeek, fNoSeek;
    unsigned short fAlignType;
    unsigned char fFlags;
    plString fAnimName;
    plKey fFinishKey;

public:
    plAvSeekMsg();
    virtual ~plAvSeekMsg();

    DECLARE_CREATABLE(plAvSeekMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plAvOneShotMsg : public plAvSeekMsg {
private:
    plString fAnimName;
    bool fDrivable, fReversible;

public:
    plAvOneShotMsg();
    virtual ~plAvOneShotMsg();

    DECLARE_CREATABLE(plAvOneShotMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
