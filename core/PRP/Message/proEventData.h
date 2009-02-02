#ifndef _PROEVENTDATA_H
#define _PROEVENTDATA_H

#include "PlasmaDefs.h"
#include "Math/hsGeometry3.h"
#include "PRP/KeyedObject/plKey.h"
#include "ResManager/plResManager.h"

#define DECLARE_EVTDATA(classname) \
    static classname* Convert(proEventData* evt);

#define IMPLEMENT_EVTDATA(classname, evtType) \
    classname* classname::Convert(proEventData* evt) { \
        if (evt != NULL && evt->EventType() == evtType) \
            return (classname*)evt; \
        return NULL; \
    }

DllClass proEventData {
public:
    enum eventType {
        kCollision = 1, kPicked, kControlKey, kVariable, kFacing, kContained,
        kActivate, kCallback, kResponderState, kMultiStage, kSpawned,
        kClickDrag, kCoop, kOfferLinkBook, kBook, kClimbingBlockerHit,
        kNone
    };

    enum dataType { kNumber, kKey, kNotta };

    enum multiStageEventType {
        kEnterStage = 1, kBeginningOfLoop, kAdvanceNextStage,
        kRegressPrevStage, kNothing
    };

private:
    static const char* const fEventNames[];

protected:
    int fEventType;

public:
    proEventData();
    virtual ~proEventData();

    int EventType() const;

    static proEventData* Read(hsStream* S, plResManager* mgr);
    void write(hsStream* S, plResManager* mgr);
    void prcWrite(pfPrcHelper* prc);
    static proEventData* PrcParse(const pfPrcTag* tag, plResManager* mgr);

protected:
    static proEventData* ICreateEventDataType(int type);
    static proEventData* ICreateEventDataType(const char* typeName);
    virtual void IRead(hsStream* S, plResManager* mgr)=0;
    virtual void IWrite(hsStream* S, plResManager* mgr)=0;
    virtual void IPrcWrite(pfPrcHelper* prc)=0;
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass proCollisionEventData : public proEventData {
protected:
    bool fEnter;
    plKey fHitter;
    plKey fHittee;

public:
    proCollisionEventData();
    DECLARE_EVTDATA(proCollisionEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool isEnter() const;
    plKey getHitter() const;
    plKey getHittee() const;

    void setEnter(bool enter);
    void setHitter(plKey hitter);
    void setHittee(plKey hittee);
};

DllClass proPickedEventData : public proEventData {
protected:
    plKey fPicker;
    plKey fPicked;
    bool fEnabled;
    hsVector3 fHitPoint;

public:
    proPickedEventData();
    DECLARE_EVTDATA(proPickedEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getPicker() const;
    plKey getPicked() const;
    bool isEnabled() const;
    hsVector3 getHitPoint() const;

    void setPicker(plKey picker);
    void setPicked(plKey picked);
    void setEnabled(bool enabled);
    void setHitPoint(const hsVector3& point);
};

DllClass proControlKeyEventData : public proEventData {
protected:
    int fControlKey;
    bool fDown;

public:
    proControlKeyEventData();
    DECLARE_EVTDATA(proControlKeyEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    int getControlKey() const;
    bool isDown() const;

    void setControlKey(int key);
    void setDown(bool down);
};

DllClass proVariableEventData : public proEventData {
protected:
    plString fName;
    int fDataType;
    float fNumber;
    plKey fKey;

public:
    proVariableEventData();
    DECLARE_EVTDATA(proVariableEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getName() const;
    int getDataType() const;
    float getNumber() const;
    plKey getKey() const;

    void setName(const plString& name);
    void setDataType(int type);
    void setNumber(float number);
    void setKey(plKey key);
};

DllClass proFacingEventData : public proEventData {
protected:
    plKey fFacer;
    plKey fFacee;
    float fDot;
    bool fEnabled;

public:
    proFacingEventData();
    DECLARE_EVTDATA(proFacingEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getFacer() const;
    plKey getFacee() const;
    float getDot() const;
    bool isEnabled() const;

    void setFacer(plKey facer);
    void setFacee(plKey facee);
    void setDot(float dot);
    void setEnabled(bool enabled);
};

DllClass proContainedEventData : public proEventData {
protected:
    plKey fContained;
    plKey fContainer;
    bool fEntering;

public:
    proContainedEventData();
    DECLARE_EVTDATA(proContainedEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getContained() const;
    plKey getContainer() const;
    bool isEntering() const;

    void setContained(plKey contained);
    void setContainer(plKey container);
    void setEntering(bool entering);
};

DllClass proActivateEventData : public proEventData {
protected:
    bool fActive, fActivate;

public:
    proActivateEventData();
    DECLARE_EVTDATA(proActivateEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool isActive() const;
    bool isActivate() const;

    void setActive(bool active);
    void setActivate(bool activate);
};

DllClass proCallbackEventData : public proEventData {
protected:
    int fCallbackEventType;

public:
    proCallbackEventData();
    DECLARE_EVTDATA(proCallbackEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    int getCallbackEventType() const;
    void setCallbackEventType(int type);
};

DllClass proResponderStateEventData : public proEventData {
protected:
    int fState;

public:
    proResponderStateEventData();
    DECLARE_EVTDATA(proResponderStateEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    int getState() const;
    void setState(int state);
};

DllClass proMultiStageEventData : public proEventData {
protected:
    int fStage, fEvent;
    plKey fAvatar;

public:
    proMultiStageEventData();
    DECLARE_EVTDATA(proMultiStageEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    int getStage() const;
    int getEvent() const;
    plKey getAvatar() const;

    void setStage(int stage);
    void setEvent(int event);
    void setAvatar(plKey avatar);
};

DllClass proSpawnedEventData : public proEventData {
protected:
    plKey fSpawner;
    plKey fSpawnee;

public:
    proSpawnedEventData();
    DECLARE_EVTDATA(proSpawnedEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getSpawner() const;
    plKey getSpawnee() const;

    void setSpawner(plKey spawner);
    void setSpawnee(plKey spawnee);
};

DllClass proClickDragEventData : public proEventData {
public:
    proClickDragEventData();
    DECLARE_EVTDATA(proClickDragEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass proCoopEventData : public proEventData {
protected:
    unsigned int fID;
    unsigned short fSerial;

public:
    proCoopEventData();
    DECLARE_EVTDATA(proCoopEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getID() const;
    unsigned short getSerial() const;

    void setID(unsigned int id);
    void setSerial(unsigned short serial);
};

DllClass proOfferLinkBookEventData : public proEventData {
protected:
    plKey fOfferer;
    int fTargetAge, fOfferee;

public:
    proOfferLinkBookEventData();
    DECLARE_EVTDATA(proOfferLinkBookEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getOfferer() const;
    int getTargetAge() const;
    int getOfferee() const;

    void setOfferer(plKey offerer);
    void setTargetAge(int age);
    void setOfferee(int offeree);
};

DllClass proBookEventData : public proEventData {
protected:
    unsigned int fEvent, fLinkID;

public:
    proBookEventData();
    DECLARE_EVTDATA(proBookEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned int getEvent() const;
    unsigned int getLinkID() const;

    void setEvent(unsigned int event);
    void setLinkID(unsigned int id);
};

DllClass proClimbingBlockerHitEventData : public proEventData {
protected:
    plKey fBlockerKey;

public:
    proClimbingBlockerHitEventData();
    DECLARE_EVTDATA(proClimbingBlockerHitEventData)

protected:
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getBlocker() const;
    void setBlocker(plKey blocker);
};

#endif
